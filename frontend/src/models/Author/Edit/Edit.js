import { useEffect, useState } from "react";
import {
    faPhotoFilm,
    faT,
    faXmark,
    faPlus,
} from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import EditMC from "./EditMC";
import EditSA from "./EditSA";
import EditTF from "./EditTF";
import { getQuiz, sendQuiz } from "./API_edit";

const starter = [
    {
        title: "a",
        type: "",
        score: "0",
        dificulty: "",
        minage: 10,
        options: [],
        contents: [],
    },
];

export default function Edit({ cookies, id }) {
    const [questions, setQuestions] = useState(starter);
    const [title, setTitle] = useState("");
    const [error, setError] = useState(null);

    const changeContentText = (e, value, questionIndex, contentIndex) => {
        e.preventDefault();
        let newQuestions = [...questions];

        newQuestions[questionIndex].contents[contentIndex]["text"] = value;

        setQuestions(newQuestions);
    };

    const newContent = (e, type, questionIndex) => {
        e.preventDefault();

        let newQuestions = [...questions];

        if (type === "T")
            newQuestions[questionIndex].contents.push({
                type: type,
                text: "",
                order: questions[questionIndex].contents.length,
            });

        setQuestions(newQuestions);
    };

    const removeContent = (e, questionIndex, contentIndex) => {
        e.preventDefault();

        let newQuestions = [...questions];
        let newContents = questions[questionIndex].contents;

        newContents.splice(contentIndex, 1);

        newQuestions[questionIndex].contents = newContents;

        setQuestions(newQuestions);
    };

    const changeType = (e, type, questionIndex) => {
        const newList =
            type === "TF"
                ? [
                      { answer: "True", correct: false },
                      { answer: "False", correct: false },
                  ]
                : [];

        let newQuestions = [...questions];

        newQuestions[questionIndex].type = type;
        newQuestions[questionIndex].options = newList;

        setQuestions(newQuestions);
    };

    const redirect = (page) => {
        window.location.href = page;
    };

    const changeDifficulty = (e, dif, questionIndex) => {
        e.preventDefault();

        let newQuestions = [...questions];

        newQuestions[questionIndex].dificulty = dif;

        setQuestions(newQuestions);
    };

    const changeMinage = (e, questionIndex) => {
        e.preventDefault();
        let result = e.target.value.replace(/\D/g, "");
        if (!result) {
            result = "0";
        }

        let newQuestions = [...questions];

        newQuestions[questionIndex].minage = result;

        setQuestions(newQuestions);
    };

    const changeScore = (e, questionIndex) => {
        e.preventDefault();
        let result = e.target.value.replace(/\D/g, "");
        if (!result) {
            result = "0";
        }
        let newQuestions = [...questions];

        newQuestions[questionIndex].score = result;

        setQuestions(newQuestions);
    };

    const changeTitle = (e) => {
        e.preventDefault();

        setTitle(e.target.value);
    };

    const newQuestion = (e) => {
        e.preventDefault();

        setQuestions([
            ...questions,
            {
                title: "a",
                type: "",
                score: "0",
                dificulty: "",
                minage: 10,
                options: [],
                contents: [],
            },
        ]);
    };

    const removeQuestion = (e, questionIndex) => {
        e.preventDefault();

        let newQuestions = [...questions];
        newQuestions.splice(questionIndex, 1);

        setQuestions(newQuestions);
    };

    async function submit(e) {
        e.preventDefault();

        try {
            const response = await sendQuiz([...questions], cookies, id, title);

            if (response) redirect("/Author/Main");
            else
                setError(
                    "Unable to add question. Check if every field is correctly filled in."
                );
        } catch (e) {
            setError("Unable to connect to database.");
        }
    }

    useEffect(() => {
        async function effect() {
            if (id) {
                try {
                    const data = await getQuiz(id, cookies);
                    setQuestions(data.questions);
                    setTitle(data.title);
                } catch (e) {
                    redirect("/");
                }
            }
        }
        effect();
    }, []);

    return (
        <>
            <div className="mt-28 flex items-center justify-center flex-col mb-10">
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
                        value={questions.title}
                        placeholder="title"
                        onChange={changeTitle}
                    ></input>
                </div>
                {questions.map((question, questionIndex) => {
                    return (
                        <>
                            {questionIndex !== 0 && (
                                <hr className="h bg-gray-900 w-[900px] mt-2 mb-5" />
                            )}
                            {questionIndex !== 0 && (
                                <button
                                    onClick={(e) =>
                                        removeQuestion(e, questionIndex)
                                    }
                                >
                                    <FontAwesomeIcon
                                        icon={faXmark}
                                        className="text-stone-400 cursor-pointer"
                                    ></FontAwesomeIcon>
                                </button>
                            )}
                            <div className="flex text-3xl py-2">Difficulty</div>
                            <div className="w-[800px] flex flex-row justify-between items-center">
                                <button
                                    className={`flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3 ${
                                        question.dificulty == "E"
                                            ? "bg-stone-200"
                                            : ""
                                    }`}
                                    onClick={(e) =>
                                        changeDifficulty(e, "E", questionIndex)
                                    }
                                >
                                    Easy
                                </button>
                                <button
                                    className={`flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3 ${
                                        question.dificulty == "M"
                                            ? "bg-stone-200"
                                            : ""
                                    }`}
                                    onClick={(e) =>
                                        changeDifficulty(e, "M", questionIndex)
                                    }
                                >
                                    Medium
                                </button>
                                <button
                                    className={`flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3 ${
                                        question.dificulty == "H"
                                            ? "bg-stone-200"
                                            : ""
                                    }`}
                                    onClick={(e) =>
                                        changeDifficulty(e, "H", questionIndex)
                                    }
                                >
                                    Hard
                                </button>
                            </div>
                            <div className="flex justify-around w-[800px]">
                                <div className="flex flex-col justify-center items-center">
                                    <div className="flex text-3xl py-2">
                                        Minimum age
                                    </div>
                                    <input
                                        type="text"
                                        value={question.minage}
                                        className="flex items-center justify-center px-3 h-12 w-20 border-2 border-stone-200 rounded-3xl mb-3"
                                        onChange={(e) =>
                                            changeMinage(e, questionIndex)
                                        }
                                    />
                                </div>
                                <div className="flex flex-col justify-center items-center">
                                    <div className="flex text-3xl py-2">
                                        Score
                                    </div>
                                    <input
                                        type="text"
                                        value={question.score}
                                        className="flex items-center justify-center px-3 h-12 w-20 border-2 border-stone-200 rounded-3xl mb-3"
                                        onChange={(e) =>
                                            changeScore(e, questionIndex)
                                        }
                                    />
                                </div>
                            </div>

                            <div className="flex text-3xl py-2">Content</div>
                            {question.contents.map((media, contentIndex) => {
                                switch (media["type"]) {
                                    case "T":
                                        return (
                                            <div
                                                className="flex items-center px-3 w-[800px] min-h-[48px] border-2 border-stone-200  rounded-3xl mb-3"
                                                key={`q${questionIndex}c${contentIndex}`}
                                            >
                                                <textarea
                                                    className="outline-0 ml-3 bg-inherit w-full pt-3"
                                                    type="text"
                                                    id={`q${questionIndex}c${contentIndex}`}
                                                    name="media"
                                                    value={media["text"]}
                                                    placeholder="Content"
                                                    onChange={(e) =>
                                                        changeContentText(
                                                            e,
                                                            e.target.value,
                                                            questionIndex,
                                                            contentIndex
                                                        )
                                                    }
                                                ></textarea>
                                                <button
                                                    onClick={(e) =>
                                                        removeContent(
                                                            e,
                                                            questionIndex,
                                                            contentIndex
                                                        )
                                                    }
                                                >
                                                    <FontAwesomeIcon
                                                        icon={faXmark}
                                                        className="text-stone-400 cursor-pointer"
                                                    ></FontAwesomeIcon>
                                                </button>
                                            </div>
                                        );
                                }
                            })}
                            <div className="flex items-center px-3 h-12 w-[800px] border-2 border-stone-200  rounded-3xl mb-3">
                                <button
                                    className="ml-3 text-stone-400"
                                    onClick={(e) =>
                                        newContent(e, "T", questionIndex)
                                    }
                                >
                                    <FontAwesomeIcon
                                        icon={faT}
                                    ></FontAwesomeIcon>
                                </button>
                                <button
                                    className="ml-3 text-stone-400"
                                    onClick={(e) =>
                                        newContent(e, "M", questionIndex)
                                    }
                                >
                                    <FontAwesomeIcon
                                        icon={faPhotoFilm}
                                    ></FontAwesomeIcon>
                                </button>
                            </div>
                            <div className="flex text-3xl py-2">Type</div>
                            <div className="w-[800px] flex flex-row justify-between items-center">
                                <button
                                    className={`flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3 ${
                                        question.type === "MC"
                                            ? "bg-stone-200"
                                            : ""
                                    }`}
                                    onClick={(e) => {
                                        changeType(e, "MC", questionIndex);
                                    }}
                                >
                                    Multiple Choice
                                </button>
                                <button
                                    className={`flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3 ${
                                        question.type === "TF"
                                            ? "bg-stone-200"
                                            : ""
                                    }`}
                                    onClick={(e) =>
                                        changeType(e, "TF", questionIndex)
                                    }
                                >
                                    True/False
                                </button>
                                <button
                                    className={`flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3 ${
                                        question.type === "SA"
                                            ? "bg-stone-200"
                                            : ""
                                    }`}
                                    onClick={(e) =>
                                        changeType(e, "SA", questionIndex)
                                    }
                                >
                                    Short Answer
                                </button>
                            </div>
                            {question.type === "MC" && (
                                <EditMC
                                    setQuestions={setQuestions}
                                    questions={questions}
                                    questionIndex={questionIndex}
                                />
                            )}
                            {question.type === "SA" && (
                                <EditSA
                                    setQuestions={setQuestions}
                                    questions={questions}
                                    questionIndex={questionIndex}
                                />
                            )}
                            {question.type === "TF" && (
                                <EditTF
                                    setQuestions={setQuestions}
                                    questions={questions}
                                    questionIndex={questionIndex}
                                />
                            )}
                        </>
                    );
                })}
                <div className="w-[800px] flex justify-around mt-6">
                    <button
                        className="px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3"
                        onClick={newQuestion}
                    >
                        <FontAwesomeIcon
                            className="text-sm"
                            icon={faPlus}
                        ></FontAwesomeIcon>{" "}
                        Add
                    </button>

                    <button
                        className="flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3"
                        onClick={(e) => submit(e)}
                    >
                        Submit
                    </button>
                </div>
            </div>
        </>
    );
}
