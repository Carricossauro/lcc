import { faPhotoFilm, faT, faPlus } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";

export default function EditSA({ setQuestion, question }) {
  const changeOption = (e, index) => {
    let newList = question.options;
    newList[index] = { answer: e.target.value, correct: 1 };

    setQuestion({ ...question, options: newList });
  };
  const newOption = (e) => {
    e.preventDefault();
    let newList = question.options;

    newList.push({ answer: "", correct: 1 });

    setQuestion({ ...question, options: newList });
  };
  return (
    <>
      {question.options.map((media, index) => {
        return (
          <div
            className="flex items-center px-3 w-[800px] min-h-[48px] border-2 border-stone-200  rounded-3xl mb-3"
            key={index}
          >
            <textarea
              className="outline-0 ml-3 bg-inherit w-full pt-3"
              type="text"
              id={`option${index}`}
              name="option"
              value={media["answer"]}
              placeholder="Option"
              onChange={(e) => changeOption(e, index)}
            ></textarea>
          </div>
        );
      })}
      <div className="flex items-center px-3 h-12 w-[800px] border-2 border-stone-200  rounded-3xl mb-3">
        <button className="ml-3 text-stone-400" onClick={(e) => newOption(e)}>
          <FontAwesomeIcon className="text-sm" icon={faPlus}></FontAwesomeIcon>{" "}
          Add
        </button>
      </div>
    </>
  );
}
