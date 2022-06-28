import { faPlus, faXmark } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";

export default function EditSA({ setQuestions, questions, questionIndex }) {
    const changeOption = (e, optionIndex) => {
        let newList = questions[questionIndex].options;
        newList[optionIndex] = { answer: e.target.value, correct: true };

        let newQuestions = [...questions];
        newQuestions[questionIndex].options = newList;

        setQuestions(newQuestions);
    };

    const newOption = (e) => {
        e.preventDefault();

        let newList = questions[questionIndex].options;
        newList.push({ answer: "", correct: true });

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

    return (
        <>
            {questions[questionIndex].options.map((media, optionIndex) => {
                return (
                    <div
                        className="flex items-center px-3 w-[800px] min-h-[48px] border-2 border-stone-200  rounded-3xl mb-3"
                        key={optionIndex}
                    >
                        <textarea
                            className="outline-0 ml-3 bg-inherit w-full pt-3"
                            type="text"
                            id={`g${questionIndex}o${optionIndex}`}
                            name="option"
                            value={media["answer"]}
                            placeholder="Option"
                            onChange={(e) => changeOption(e, optionIndex)}
                        ></textarea>
                        <button onClick={(e) => removeOption(e, optionIndex)}>
                            <FontAwesomeIcon
                                icon={faXmark}
                                className="text-stone-400 cursor-pointer"
                            ></FontAwesomeIcon>
                        </button>
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
