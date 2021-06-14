import * as nbind from "nbind";
import * as LibTypes from "./types/lib-types";
const lib = nbind.init<typeof LibTypes>().lib;

const Connect4HelloWorld = () => {
  const mySayHello = (name: string) => {
    return lib.Greeter.sayHello(name);
  };
  const myMultiply = (a: number, b: number) => {
    const g = new lib.Greeter();
    return g.multiply(a, b);
  };
  return { mySayHello, myMultiply };
};

export default Connect4HelloWorld;
