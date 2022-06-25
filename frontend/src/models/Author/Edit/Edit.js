import { useState } from "react";
import { faPhotoFilm, faT, faPlus } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import EditMC from "./EditMC";
import EditSA from "./EditSA";
import EditTF from "./EditTF";
import { sendQuestion } from "./API_edit";

// TODO - add delete button on content and options

export default function Edit() {
    const [question, setQuestion] = useState({
        title: "",
        author: "sauro",
        type: "",
        score: "0",
        difficulty: "",
        minage: 10,
        options: [],
        content: [],
    });
    const [error, setError] = useState(null);

    const changeContentText = (value, index) => {
        let newList = question.content;

        newList[index]["text"] = value;

        return newList;
    };

    const newContent = (type, e) => {
        e.preventDefault();
        let newList = question.content;

        if (type == "T")
            newList.push({ type: type, text: "", order: newList.length });

        setQuestion({ ...question, content: newList });
    };

    const changeType = (e, type) => {
        e.preventDefault();

        let newList = [];

        if (type === "TF") newList = [{ answer: "True" }, { answer: "False" }];

        setQuestion({ ...question, type: type, options: newList });
    };

    const redirect = (page) => {
        window.location.href = page;
    };

    const changeDifficulty = (e, diff) => {
        e.preventDefault();

        setQuestion({ ...question, difficulty: diff });
    };

    const changeMinage = (e) => {
        e.preventDefault();
        let result = e.target.value.replace(/\D/g, "");
        if (!result) {
            result = "0";
        }
        setQuestion({ ...question, minage: parseInt(result) });
    };

    const changeScore = (e) => {
        e.preventDefault();
        let result = e.target.value.replace(/\D/g, "");
        if (!result) {
            result = "0";
        }
        setQuestion({ ...question, score: parseInt(result) });
    };

    async function submit(e) {
        e.preventDefault();

        try {
            const response = await sendQuestion(question);

            if (response) redirect("/Author/Main");
            else
                setError(
                    "Unable to add question. Check if every field is correctly filled in."
                );
        } catch (e) {
            setError("Unable to connect to database.");
        }
    }

    return (
        <>
            <form className="mt-28 flex items-center justify-center flex-col">
                {error && (
                    <div className="w-[750px] border text-red-700 mb-3 rounded-md bg-red-100 flex justify-center p-2">
                        {error}
                    </div>
                )}
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
                <div className="flex text-3xl py-2">Difficulty</div>
                <div className="w-[800px] flex flex-row justify-between items-center">
                    <button
                        className={`flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3 ${
                            question.difficulty == "Easy" ? "bg-stone-200" : ""
                        }`}
                        onClick={(e) => changeDifficulty(e, "Easy")}
                    >
                        Easy
                    </button>
                    <button
                        className={`flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3 ${
                            question.difficulty == "Medium"
                                ? "bg-stone-200"
                                : ""
                        }`}
                        onClick={(e) => changeDifficulty(e, "Medium")}
                    >
                        Medium
                    </button>
                    <button
                        className={`flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3 ${
                            question.difficulty == "Hard" ? "bg-stone-200" : ""
                        }`}
                        onClick={(e) => changeDifficulty(e, "Hard")}
                    >
                        Hard
                    </button>
                </div>
                <div className="flex justify-around w-[800px]">
                    <div className="flex flex-col justify-center items-center">
                        <div className="flex text-3xl py-2">Minimum age</div>
                        <input
                            type="text"
                            value={question.minage}
                            className="flex items-center justify-center px-3 h-12 w-20 border-2 border-stone-200 rounded-3xl mb-3"
                            onChange={(e) => changeMinage(e)}
                        />
                    </div>
                    <div className="flex flex-col justify-center items-center">
                        <div className="flex text-3xl py-2">Score</div>
                        <input
                            type="text"
                            value={question.score}
                            className="flex items-center justify-center px-3 h-12 w-20 border-2 border-stone-200 rounded-3xl mb-3"
                            onChange={(e) => changeScore(e)}
                        />
                    </div>
                </div>

                <div className="flex text-3xl py-2">Content</div>
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
                                        value={question.content[index]["text"]}
                                        placeholder="Content"
                                        onChange={(e) =>
                                            setQuestion({
                                                ...question,
                                                content: changeContentText(
                                                    e.target.value,
                                                    index
                                                ),
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
                <div className="flex text-3xl py-2">Type</div>
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
                {question.type === "MC" && (
                    <EditMC setQuestion={setQuestion} question={question} />
                )}
                {question.type === "SA" && (
                    <EditSA setQuestion={setQuestion} question={question} />
                )}
                {question.type === "TF" && (
                    <EditTF setQuestion={setQuestion} question={question} />
                )}
                <div className="w-[800px] flex justify-end mt-6">
                    <button
                        className="flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3"
                        onClick={(e) => submit(e)}
                    >
                        Submit
                    </button>
                </div>
            </form>
        </>
    );
}
