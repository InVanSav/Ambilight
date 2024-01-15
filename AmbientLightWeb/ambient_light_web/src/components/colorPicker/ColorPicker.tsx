import React from "react";
import { SketchPicker, ColorResult } from "react-color";

interface ColorPickerProps {
  color: string;
  onChange: (color: ColorResult) => void;
}

const ColorPicker: React.FC<ColorPickerProps> = ({ color, onChange }) => {
  const handleColorChange = (color: ColorResult) => {
    onChange(color);
  };

  return (
    <SketchPicker
      color={color}
      onChange={handleColorChange}
      disableAlpha={true}
    />
  );
};

export default ColorPicker;
