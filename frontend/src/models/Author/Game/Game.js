import GameTF from "./GameTF";
import GameMC from "./GameMC";
import GameSA from "./GameSA";

export default function Game({ question }) {
    return (
        <>
            <div className="">
                {question.contents.map((media, index) => {
                    switch (media["type"]) {
                        case "T":
                            return (
                                <div
                                    className="flex items-center px-3 w-[350px] lg:w-[800px] min-h-[48px] text-justify rounded-3xl mb-3"
                                    key={index}
                                >
                                    {question.contents[index]["text"]}
                                </div>
                            );
                        default:
                            return "";
                    }
                })}
                {question.type === "MC" && <GameMC question={question} />}
                {question.type === "SA" && <GameSA question={question} />}
                {question.type === "TF" && <GameTF question={question} />}
            </div>
        </>
    );
}
