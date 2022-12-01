export default function gameTF({ question }) {
    return (
        <div className="w-[350px] lg:w-[800px] flex flex-row justify-around items-center gap-x-2">
            {question.options.map((option, index) => {
                return (
                    <div
                        className={`flex items-center justify-center px-3 h-12 w-1/2 border-2 border-stone-200 rounded-3xl mb-3 ${
                            option.correct ? "bg-green-500" : ""
                        }`}
                        key={index}
                    >
                        {option.answer}
                    </div>
                );
            })}
        </div>
    );
}
