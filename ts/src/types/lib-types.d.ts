import { Buffer } from "nbind/dist/shim";

export class NBindBase { free?(): void }

export class Game extends NBindBase {
	/** Game(std::string); */
	constructor(p0: string);

	/** void play(const int32_t &); */
	play(p0: number): void;

	/** Game(std::string); */
	constructor(p0: string);

	/** void play(const int32_t &); */
	play(p0: number): void;
}

export class NegamaxBot extends NBindBase {
	/** NegamaxBot(); */
	constructor();

	/** int32_t getBestMove(const Game &); */
	getBestMove(p0: Game): number;
}
