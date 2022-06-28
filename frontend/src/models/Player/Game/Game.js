import GameTF from "./GameTF";
import GameMC from "./GameMC";
import GameSA from "./GameSA";

export default function Game({ question, answers, setAnswers, questionIndex }) {
    return (
        <>
            {question && (
                <div className="" key={`q${questionIndex}`}>
                    {question.contents.map((media, contentIndex) => {
                        switch (media["type"]) {
                            case "T":
                                return (
                                    <div
                                        className="flex items-center px-3 w-[800px] min-h-[48px] text-justify rounded-3xl mb-3"
                                        key={`q${questionIndex}c${contentIndex}`}
                                    >
                                        {
                                            question.contents[contentIndex][
                                                "text"
                                            ]
                                        }
                                    </div>
                                );
                        }
                    })}
                    {question.type === "MC" && (
                        <GameMC
                            question={question}
                            answers={answers}
                            setAnswers={setAnswers}
                            questionIndex={questionIndex}
                        />
                    )}
                    {question.type === "SA" && (
                        <GameSA
                            question={question}
                            answers={answers}
                            setAnswers={setAnswers}
                            questionIndex={questionIndex}
                        />
                    )}
                    {question.type === "TF" && (
                        <GameTF
                            question={question}
                            answers={answers}
                            setAnswers={setAnswers}
                            questionIndex={questionIndex}
                        />
                    )}
                </div>
            )}
        </>
    );
}
