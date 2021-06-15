import * as nbind from "nbind";
import * as LibTypes from "./types/lib-types";
const lib = nbind.init<typeof LibTypes>().lib;

export const NegamaxBot = lib.NegamaxBot;
export const Game = lib.NegamaxBot;
