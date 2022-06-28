export default function GameSA({ answers, setAnswers, questionIndex }) {
    const changeOption = (e) => {
        e.preventDefault();

        let newAnswers = { ...answers };
        newAnswers[questionIndex] = e.target.value;
        setAnswers(newAnswers);
    };
    return (
        <>
            <div className="flex items-center px-3 w-[800px] min-h-[48px] border-2 border-stone-200  rounded-3xl mb-3">
                <textarea
                    className="outline-0 ml-3 bg-inherit w-full pt-3"
                    type="text"
                    id="1"
                    name="ans"
                    value={answers[questionIndex]}
                    placeholder="Answer"
                    onChange={(e) => changeOption(e)}
                ></textarea>
            </div>
        </>
    );
}
