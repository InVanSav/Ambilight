import React, { useState, ChangeEvent } from "react";
import "./InputFields.css";

interface InputFieldsProps {
  onIpChange: (value: string, isValid: boolean) => void;
  onPortChange: (value: string, isValid: boolean) => void;
}

const InputFields: React.FC<InputFieldsProps> = ({
  onIpChange,
  onPortChange,
}) => {
  const [ip, setIp] = useState<string>("");
  const [port, setPort] = useState<string>("");
  const [ipValid, setIpValid] = useState<boolean>(true);
  const [portValid, setPortValid] = useState<boolean>(true);

  const validateIp = (value: string): boolean => {
    return /^(\d{1,3}\.){3}\d{1,3}$/.test(value);
  };

  const validatePort = (value: string): boolean => {
    const portNumber = parseInt(value, 10);
    return !isNaN(portNumber) && portNumber >= 0 && portNumber <= 65535;
  };

  const handleIpChange = (event: ChangeEvent<HTMLInputElement>) => {
    const value = event.target.value;
    const isValid = validateIp(value);
    setIp(value);
    setIpValid(isValid);
    onIpChange(value, isValid);
  };

  const handlePortChange = (event: ChangeEvent<HTMLInputElement>) => {
    const value = event.target.value;
    const isValid = validatePort(value);
    setPort(value);
    setPortValid(isValid);
    onPortChange(value, isValid);
  };

  return (
    <div className="main_setting_items">
      <input
        className={`setting_input ${ipValid ? "" : "invalid"}`}
        type="text"
        placeholder="Enter IP"
        value={ip}
        onChange={handleIpChange}
      />
      <input
        className={`setting_input ${portValid ? "" : "invalid"}`}
        type="text"
        placeholder="Enter Port"
        value={port}
        onChange={handlePortChange}
      />
    </div>
  );
};

export default InputFields;
