import { faCheck, faPlus, faXmark } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";

export default function EditMC({ setQuestion, question }) {
    const changeOption = (e, option, index, value) => {
        e.preventDefault();
        let newList = question.options;

        for (var i = 0; i < newList.length; i++) {
            if (i !== index) {
                if (value) newList[i] = { ...newList[i], correct: false };
            } else newList[i] = { answer: option, correct: value };
        }

        setQuestion({ ...question, options: newList });
    };

    const removeOption = (e, index) => {
        e.preventDefault();
        let newList = question.options;
        newList.splice(index, 1);

        setQuestion({ ...question, options: newList });
    };

    const newOption = (e) => {
        e.preventDefault();
        let newList = question.options;

        newList.push({ answer: "", correct: 0 });

        setQuestion({ ...question, options: newList });
    };
    return (
        <>
            {question.options.map((media, index) => {
                return (
                    <div
                        className="w-[800px] flex-row flex items-center pl-3 mb-3"
                        key={index}
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
                                    index,
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
                                        index,
                                        media.correct
                                    )
                                }
                            ></input>
                            <button onClick={(e) => removeOption(e, index)}>
                                <FontAwesomeIcon
                                    icon={faXmark}
                                    className="text-stone-400 cursor-pointer"
                                ></FontAwesomeIcon>
                            </button>
                        </div>
                    </div>
                );
            })}
            <div className="flex items-center px-3 h-12 w-[800px] border-2 border-stone-200  rounded-3xl mb-3">
                <button
                    className="ml-3 text-stone-400"
                    onClick={(e) => newOption(e)}
                >
                    <FontAwesomeIcon
                        className="text-sm"
                        icon={faPlus}
                    ></FontAwesomeIcon>{" "}
                    Add
                </button>
            </div>
        </>
    );
}
