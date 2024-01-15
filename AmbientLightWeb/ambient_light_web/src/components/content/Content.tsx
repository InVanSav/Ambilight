import React, { useState } from "react";
import InputFields from "../inputFields/InputFields";
import DropdownList from "../dropdownList/DropdownList";
import ColorPicker from "../colorPicker/ColorPicker";
import "./Content.css";
import { RGBColor } from "react-color";

const Content: React.FC = () => {
  const [selectedItem, setSelectedItem] = useState<string>("Ambilight");
  const [selectedColor, setSelectedColor] = useState<string>("#ffffff");
  const [ip, setIp] = useState<string>("");
  const [port, setPort] = useState<string>("");

  const handleIpChange = (value: string, isValid: boolean) => {
    setIp(value);
    console.log(`IP: ${value}, isValid: ${isValid}`);
  };

  const handlePortChange = (value: string, isValid: boolean) => {
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

  const handleSendData = () => {
    console.log("Sending data:", {
      ip,
      port,
      color: selectedColor,
    });
    // Логика для отправки данных
  };

  return (
    <div className="content">
      <div className="content_main">
        <InputFields
          onIpChange={handleIpChange}
          onPortChange={handlePortChange}
        />
        <DropdownList onItemSelected={handleDropdownChange} />
        <div className="main_setting_items">
          {selectedItem === "Static color" && (
            <div className="color_picker_container">
              <ColorPicker color={selectedColor} onChange={handleColorChange} />
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
            <div className="ambilight_container">Тут должно быть что-то</div>
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
