"use strict";
exports.__esModule = true;
var nbind = require("nbind");
var lib = nbind.init().lib;
var Connect4HelloWorld = function () {
    var mySayHello = function (name) {
        return lib.Greeter.sayHello(name);
    };
    var myMultiply = function (a, b) {
        var g = new lib.Greeter();
        return g.multiply(a, b);
    };
    return { mySayHello: mySayHello, myMultiply: myMultiply };
};
exports["default"] = Connect4HelloWorld;
