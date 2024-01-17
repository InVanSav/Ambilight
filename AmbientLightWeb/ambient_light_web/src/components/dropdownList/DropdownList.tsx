import React, { useState } from "react";
import "./DropdownList.css";

interface DropdownListProps {
  onItemSelected: (item: string) => void;
}

const DropdownList: React.FC<DropdownListProps> = ({ onItemSelected }) => {
  const [selectedItem, setSelectedItem] = useState<string>("ambilight");

  const items = ["Ambilight", "Static color"];

  const handleItemClick = (item: string) => {
    setSelectedItem(item);
    onItemSelected(item);
  };

  return (
    <div className="dropdown_list">
      <select
        className="select_list dropdown"
        value={selectedItem}
        onChange={(e) => handleItemClick(e.target.value)}
      >
        {items.map((item) => (
          <option className="option_list_item dropdown" key={item} value={item}>
            {item}
          </option>
        ))}
      </select>
    </div>
  );
};

export default DropdownList;
