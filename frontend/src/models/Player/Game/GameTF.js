export default function gameTF({ question, answer, setAnswer }) {
  const changeOption = (e) => {
    e.preventDefault();
    const answer = e.target.innerHTML;
    setAnswer(answer);
  };
  return (
    <div className="w-[800px] flex flex-row justify-around items-center gap-x-2">
      {question.options.map((option, index) => {
        return (
          <button
            className={`flex items-center justify-center px-3 h-12 w-1/2 border-2 border-stone-200 rounded-3xl mb-3 ${
              answer === option.answer ? "bg-green-500" : ""
            }`}
            key={index}
            onClick={(e) => changeOption(e)}
          >
            {option.answer}
          </button>
        );
      })}
    </div>
  );
}
