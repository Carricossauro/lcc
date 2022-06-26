export default function GameSA({ question }) {
    return (
        <>
            {question.options.map((option, index) => {
                return (
                    <div
                        className="flex items-center px-3 w-[800px] min-h-[48px] border-2 border-stone-200  rounded-3xl mb-3"
                        key={`option${index}`}
                    >
                        <div className="outline-0 ml-3 bg-inherit w-full">
                            {option.answer}
                        </div>
                    </div>
                );
            })}
        </>
    );
}
