import { useState } from "react";
import { faPhotoFilm, faT } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";

export default function Edit() {
  const [question, setQuestion] = useState({
    title: "",
    type: "",
    score: 0,
    difficulty: "",
    minage: 0,
    options: [],
    content: [],
  });

  const changeContent = (value, index) => {
    let newList = question.content;

    newList[index]["media"] = value;

    return newList;
  };

  const newContent = (type, e) => {
    e.preventDefault();
    let newList = question.content;

    newList.push({ type: type, media: "" });

    setQuestion({ ...question, content: newList });
  };

  const changeType = (e, type) => {
    e.preventDefault();

    setQuestion({ ...question, type: type });
  };

  return (
    <>
      <form className="mt-28 flex items-center justify-center flex-col">
        <div className="flex items-center px-3 h-12 w-[800px] border-2 border-stone-200  rounded-3xl mb-3">
          <input
            className="outline-0 ml-3 bg-inherit w-full"
            type="textarea"
            id="title"
            name="title"
            value={question.title}
            placeholder="title"
            onChange={(e) =>
              setQuestion({ ...question, title: e.target.value })
            }
          ></input>
        </div>
        {question.content.map((media, index) => {
          switch (media["type"]) {
            case "T":
              return (
                <div
                  className="flex items-center px-3 w-[800px] min-h-[48px] border-2 border-stone-200  rounded-3xl mb-3"
                  key={index}
                >
                  <textarea
                    className="outline-0 ml-3 bg-inherit w-full pt-3"
                    type="text"
                    id={`media${index}`}
                    name="media"
                    value={question.content[index]["media"]}
                    placeholder="Content"
                    onChange={(e) =>
                      setQuestion({
                        ...question,
                        content: changeContent(e.target.value, index),
                      })
                    }
                  ></textarea>
                </div>
              );
          }
        })}
        <div className="flex items-center px-3 h-12 w-[800px] border-2 border-stone-200  rounded-3xl mb-3">
          <button
            className="ml-3 text-stone-400"
            onClick={(e) => newContent("T", e)}
          >
            <FontAwesomeIcon icon={faT}></FontAwesomeIcon>
          </button>
          <button
            className="ml-3 text-stone-400"
            onClick={(e) => newContent("M", e)}
          >
            <FontAwesomeIcon icon={faPhotoFilm}></FontAwesomeIcon>
          </button>
        </div>
        <div className="w-[800px] flex flex-row justify-between items-center">
          <button
            className={`flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3 ${
              question.type == "MC" ? "bg-stone-200" : ""
            }`}
            onClick={(e) => changeType(e, "MC")}
          >
            Multiple Choice
          </button>
          <button
            className={`flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3 ${
              question.type == "TF" ? "bg-stone-200" : ""
            }`}
            onClick={(e) => changeType(e, "TF")}
          >
            True/False
          </button>
          <button
            className={`flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3 ${
              question.type == "SA" ? "bg-stone-200" : ""
            }`}
            onClick={(e) => changeType(e, "SA")}
          >
            Short Answer
          </button>
        </div>
        <div className="w-[800px] flex justify-end mt-6">
          <button className="flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3">
            Submit
          </button>
        </div>
      </form>
    </>
  );
}
