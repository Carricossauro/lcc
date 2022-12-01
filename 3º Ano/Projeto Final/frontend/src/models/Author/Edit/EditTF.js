export default function editTF({ setQuestions, questions, questionIndex }) {
    const changeOption = (e) => {
        e.preventDefault();
        const isTrue = e.target.innerHTML === "True" ? true : false;

        const newList = [
            { answer: "True", correct: isTrue },
            { answer: "False", correct: !isTrue },
        ];

        let newQuestions = [...questions];
        newQuestions[questionIndex].options = newList;

        setQuestions(newQuestions);
    };

    return (
        <div className="w-[350px] lg:w-[800px] flex flex-row justify-around items-center gap-x-2">
            {questions[questionIndex].options.map((option, optionIndex) => {
                return (
                    <button
                        className={`flex items-center justify-center px-3 h-12 w-1/2 border-2 border-stone-200 rounded-3xl mb-3 ${
                            option.correct
                                ? "border-color5 bg-color5 text-white font-bold"
                                : "bg-stone-100 border-stone-100"
                        }`}
                        key={`g${questionIndex}o${optionIndex}`}
                        onClick={(e) => changeOption(e)}
                    >
                        {option.answer}
                    </button>
                );
            })}
        </div>
    );
}
