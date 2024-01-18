export interface Mode {
  code: number;
  body: string;
}

export interface RequestData {
  active: boolean;
  inverse: boolean;
  brightness: number;
  mode: Mode;
}
