import { Buffer } from "nbind/dist/shim";

export class NBindBase { free?(): void }

export class Greeter extends NBindBase {
	/** Greeter(); */
	constructor();

	/** static void sayHello(std::string); */
	static sayHello(p0: string): void;

	/** int32_t multiply(int32_t, int32_t); */
	multiply(p0: number, p1: number): number;
}
