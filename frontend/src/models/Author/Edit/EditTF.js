export default function editTF({ setQuestion, question }) {
  const changeOption = (e) => {
    e.preventDefault();
    const isTrue = e.target.innerHTML === "True" ? 1 : 0;

    const newList = [
      { answer: "True", correct: isTrue },
      { answer: "False", correct: (isTrue + 1) % 2 },
    ];
    setQuestion({ ...question, options: newList });
  };
  return (
    <div className="w-[800px] flex flex-row justify-around items-center gap-x-2">
      {question.options.map((option, index) => {
        return (
          <button
            className={`flex items-center justify-center px-3 h-12 w-1/2 border-2 border-stone-200 rounded-3xl mb-3 ${
              option.correct ? "bg-stone-200" : ""
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
