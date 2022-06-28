export default function gameTF({
    question,
    answers,
    setAnswers,
    questionIndex,
}) {
    const changeOption = (e) => {
        e.preventDefault();

        let newAnswers = { ...answers };
        newAnswers[questionIndex] = e.target.innerHTML;

        setAnswers(newAnswers);
    };

    return (
        <div className="w-[800px] flex flex-row justify-around items-center gap-x-2">
            {question.options.map((option, optionIndex) => {
                return (
                    <button
                        className={`flex items-center justify-center px-3 h-12 w-1/2 border-2 border-stone-200 rounded-3xl mb-3 ${
                            answers[questionIndex] === option.answer
                                ? "bg-green-500"
                                : ""
                        }`}
                        key={`q${questionIndex}o${optionIndex}`}
                        onClick={(e) => changeOption(e)}
                    >
                        {option.answer}
                    </button>
                );
            })}
        </div>
    );
}
