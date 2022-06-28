import { faCheck, faPlus, faXmark } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";

export default function EditMC({ setQuestions, questions, questionIndex }) {
    const changeOption = (e, option, optionIndex, value) => {
        e.preventDefault();
        let newList = questions[questionIndex].options;

        for (var i = 0; i < newList.length; i++) {
            if (i !== optionIndex) {
                if (value) newList[i] = { ...newList[i], correct: false };
            } else newList[i] = { answer: option, correct: value };
        }

        let newQuestions = [...questions];

        newQuestions[questionIndex].options = newList;
        setQuestions(newQuestions);
    };

    const removeOption = (e, optionIndex) => {
        e.preventDefault();

        let newList = questions[questionIndex].options;
        newList.splice(optionIndex, 1);

        let newQuestions = [...questions];
        newQuestions[questionIndex].options = newList;

        setQuestions(newQuestions);
    };

    const newOption = (e) => {
        e.preventDefault();
        let newList = questions[questionIndex].options;

        newList.push({ answer: "", correct: false });

        let newQuestions = [...questions];
        newQuestions[questionIndex].options = newList;

        setQuestions(newQuestions);
    };
    return (
        <>
            {questions[questionIndex].options.map((media, optionIndex) => {
                return (
                    <div
                        className="w-[800px] flex-row flex items-center pl-3 mb-3"
                        key={`q${questionIndex}o${optionIndex}`}
                    >
                        <button
                            className={`border-2 border-stone-200 rounded-full h-[30px] w-[30px] mr-2 flex items-center justify-center ${
                                media.correct
                                    ? "bg-green-500 text-green-50 border-green-500"
                                    : "text-stone-400"
                            }`}
                            onClick={(e) =>
                                changeOption(
                                    e,
                                    media.answer,
                                    optionIndex,
                                    !media.correct
                                )
                            }
                        >
                            <FontAwesomeIcon
                                className="text-sm"
                                icon={faCheck}
                            ></FontAwesomeIcon>
                        </button>
                        <div className="flex items-center px-3 h-[48px] border-2 border-stone-200 rounded-3xl w-full">
                            <input
                                className="outline-0 ml-3 bg-inherit w-full"
                                type="text"
                                name="option"
                                value={media["answer"]}
                                placeholder="Option"
                                onChange={(e) =>
                                    changeOption(
                                        e,
                                        e.target.value,
                                        optionIndex,
                                        media.correct
                                    )
                                }
                            ></input>
                            <button
                                onClick={(e) => removeOption(e, optionIndex)}
                            >
                                <FontAwesomeIcon
                                    icon={faXmark}
                                    className="text-stone-400 cursor-pointer"
                                ></FontAwesomeIcon>
                            </button>
                        </div>
                    </div>
                );
            })}
            <button
                className="flex items-center px-3 h-12 w-[800px] border-2 border-stone-200  rounded-3xl mb-3"
                onClick={(e) => newOption(e)}
            >
                <div className="ml-3 text-stone-400">
                    <FontAwesomeIcon
                        className="text-sm"
                        icon={faPlus}
                    ></FontAwesomeIcon>{" "}
                    Add
                </div>
            </button>
        </>
    );
}
