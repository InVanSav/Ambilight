import { RequestData } from "../types/common";

const BASE_URL = "http://your-api-base-url/";

export const fetchData = async (endpoint: string) => {
  const url = `${BASE_URL}${endpoint}`;
  const requestOptions = {
    method: "GET",
    headers: {
      "Content-Type": "application/json",
    },
  };

  try {
    const response = await fetch(url, requestOptions);

    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }

    return response.json();
  } catch (error) {
    throw new Error(`Error fetching data: ${error}`);
  }
};

export const postData = async (endpoint: string, data: any): Promise<RequestData> => {
  const url = `${BASE_URL}${endpoint}`;
  const requestOptions = {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(data),
  };

  try {
    const response = await fetch(url, requestOptions);

    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }

    return response.json();
  } catch (error) {
    throw new Error(`Error sending data: ${error}`);
  }
};
