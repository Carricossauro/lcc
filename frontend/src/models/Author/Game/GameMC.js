export default function GameMC({ question }) {
    return (
        <>
            {question.options.map((option, index) => {
                return (
                    <div
                        className={`w-[350px] lg:w-[800px] flex-row flex items-center pl-3 mb-3`}
                        key={`option${index}`}
                    >
                        <div
                            className={`${
                                option.correct ? "bg-green-500" : ""
                            } flex items-center px-3 h-[48px] border-2 border-stone-200 rounded-3xl w-full`}
                        >
                            {option["answer"]}
                        </div>
                    </div>
                );
            })}
        </>
    );
}
