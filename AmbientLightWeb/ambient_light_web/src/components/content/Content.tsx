import React, { useState } from "react";
import InputFields from "../inputFields/InputFields";
import DropdownList from "../dropdownList/DropdownList";
import ColorPicker from "../colorPicker/ColorPicker";
import "./Content.css";
import { RGBColor } from "react-color";

interface Mode {
  code: number;
  body: string;
}

interface RequestData {
  active: boolean;
  inverse: boolean;
  brightness: number;
  mode: Mode;
}

const Content: React.FC = () => {
  const [selectedItem, setSelectedItem] = useState<string>("Ambilight");
  const [selectedColor, setSelectedColor] = useState<string>("#ffffff");
  const [showServerSettings, setShowServerSettings] = useState<boolean>(false);

  const [ip, setIp] = useState<string>("");
  const [isIpValid, setIsIpValid] = useState<boolean>(false);

  const [port, setPort] = useState<string>("");
  const [isPortValid, setIsPortValid] = useState<boolean>(false);

  const [isOn, setIsOn] = useState<boolean>(true);
  const [isInverted, setIsInverted] = useState<boolean>(true);
  const [sliderValue, setSliderValue] = useState<number>(50);

  const handleIpChange = (value: string, isValid: boolean) => {
    setIsIpValid(isValid);
    setIp(value);
    console.log(`IP: ${value}, isValid: ${isValid}`);
  };

  const handlePortChange = (value: string, isValid: boolean) => {
    setIsPortValid(isValid);
    setPort(value);
    console.log(`Port: ${value}, isValid: ${isValid}`);
  };

  const handleDropdownChange = (selectedItem: string) => {
    console.log(`Selected Item: ${selectedItem}`);
    setSelectedItem(selectedItem);
  };

  const handleColorChange = (color: any) => {
    console.log(`Selected Color: ${color.hex}`);
    setSelectedColor(color.hex);
  };

  const handleCheckboxChange = (checkboxType: string) => {
    if (checkboxType === "onOff") {
      setIsOn(!isOn);
      console.log(`On/off checkbox is now ${!isOn}`);
    } else if (checkboxType === "invert") {
      setIsInverted(!isInverted);
      console.log(`Invert checkbox is now ${!isInverted}`);
    }
  };

  const handleSliderChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    const value = parseInt(event.target.value, 10);
    setSliderValue(value);
    console.log(`Slider Value: ${value}`);
  };

  const handleSendData = async () => {
    if (!isIpValid || !isPortValid) return;

    const requestData: RequestData = {
      active: isOn,
      inverse: isInverted,
      brightness: sliderValue,
      mode: {
        code: selectedItem === "Static color" ? 110 : 100,
        body: selectedItem === "Static color" ? selectedColor : "",
      },
    };

    console.log(requestData);

    const requestOptions = {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(requestData),
    };

    try {
      const response = await fetch(`http://${ip}:${port}`, requestOptions);

      if (!response.ok) {
        throw new Error(`HTTP error! Status: ${response.status}`);
      }

      console.log("Data sent successfully!");
    } catch (error) {
      console.error("Error sending data:", error);
    }
  };

  return (
    <div className="content">
      <div className="content_main">
        <div className="setting_container">
          <div className="container_selecting">
            <div className="container_checkboxes">
              <div className="selecting_checkboxes">
                <label className="label_container_checkboxes label">
                  <div>On/off</div>
                  <input
                    type="checkbox"
                    checked={isOn}
                    onChange={() => handleCheckboxChange("onOff")}
                  />
                </label>
                <label className="label_container_checkboxes label">
                  <div>Invert</div>
                  <input
                    type="checkbox"
                    checked={isInverted}
                    onChange={() => handleCheckboxChange("invert")}
                  />
                </label>
              </div>
              <label className="label_container label">
                <div className="slider_value">Brightness: {sliderValue}</div>
                <input
                  type="range"
                  min={0}
                  max={100}
                  step={1}
                  value={sliderValue}
                  onChange={handleSliderChange}
                />
              </label>
            </div>
            <DropdownList onItemSelected={handleDropdownChange} />
          </div>
          <div className="main_setting_items">
            {selectedItem === "Static color" && (
              <div className="color_picker_container">
                <ColorPicker
                  color={selectedColor}
                  onChange={handleColorChange}
                />
                <div className="color_fields">
                  <div>Selected color</div>
                  <div className="color_field">{selectedColor}</div>
                  <div className="color_field">
                    {convertColorToRGB(selectedColor)}
                  </div>
                </div>
              </div>
            )}
            {selectedItem === "Ambilight" && (
              <div className="ambilight_container"></div>
            )}
          </div>
        </div>
        <div className="hidden_buttons">
          <button
            className="server_settings_button"
            onClick={() => setShowServerSettings(!showServerSettings)}
          >
            <div className="server_settings_text">
              <div>Server settings</div>
              <img className="img_down_arrow" alt="Down Arrow" />
            </div>
          </button>
          {showServerSettings && (
            <div className="server_settings">
              <InputFields
                onIpChange={handleIpChange}
                onPortChange={handlePortChange}
              />
            </div>
          )}
        </div>
        <button className="send_button" onClick={handleSendData}>
          Submit
        </button>
      </div>
    </div>
  );
};

const convertColorToRGB = (color: string): string => {
  const { r, g, b } = hexToRgb(color);
  return `rgb(${r}, ${g}, ${b})`;
};

const hexToRgb = (hex: string): RGBColor => {
  const bigint = parseInt(hex.slice(1), 16);
  const r = (bigint >> 16) & 255;
  const g = (bigint >> 8) & 255;
  const b = bigint & 255;
  return { r, g, b };
};

export default Content;
