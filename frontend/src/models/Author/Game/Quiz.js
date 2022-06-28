import { useEffect, useState } from "react";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faPencil } from "@fortawesome/free-solid-svg-icons";
import Game from "./Game";
import { getQuiz } from "./API_game";

const example = {
    id: 1,
    questions: [
        {
            id: 1,
            author: "a",
            title: "title 1",
            type: "TF",
            score: 1,
            dificulty: "E",
            minage: 10,
            options: [
                {
                    id: 1,
                    answer: "True",
                    question: 1,
                    correct: true,
                },
                {
                    id: 2,
                    answer: "False",
                    question: 1,
                    correct: false,
                },
            ],
            contents: [
                {
                    id: 1,
                    question: 1,
                    order: 0,
                    type: "T",
                    text: "content 1 for title 1",
                    media: null,
                },
            ],
            quiz: 1,
        },
        {
            id: 2,
            author: "a",
            title: "title 2",
            type: "SA",
            score: 2,
            dificulty: "M",
            minage: 10,
            options: [
                {
                    id: 3,
                    answer: "[ ]*(?i:ola)[ ]*",
                    question: 2,
                    correct: true,
                },
            ],
            contents: [
                {
                    id: 2,
                    question: 2,
                    order: 0,
                    type: "T",
                    text: "content 1 for title 2",
                    media: null,
                },
                {
                    id: 3,
                    question: 2,
                    order: 1,
                    type: "T",
                    text: "content 2 for title 2",
                    media: null,
                },
            ],
            quiz: 1,
        },
        {
            id: 3,
            author: "a",
            title: "title 3",
            type: "MC",
            score: 8,
            dificulty: "H",
            minage: 10,
            options: [
                {
                    id: 4,
                    answer: "1",
                    question: 3,
                    correct: false,
                },
                {
                    id: 5,
                    answer: "2",
                    question: 3,
                    correct: true,
                },
                {
                    id: 6,
                    answer: "3",
                    question: 3,
                    correct: false,
                },
            ],
            contents: [
                {
                    id: 4,
                    question: 3,
                    order: 0,
                    type: "T",
                    text: "content 1 for title 3",
                    media: null,
                },
                {
                    id: 5,
                    question: 3,
                    order: 1,
                    type: "T",
                    text: "content 2 for title 3",
                    media: null,
                },
                {
                    id: 6,
                    question: 3,
                    order: 2,
                    type: "T",
                    text: "content 3 for title 3",
                    media: null,
                },
            ],
            quiz: 1,
        },
    ],
    author: "a",
    title: "Quiz 1",
};

export default function Quiz({ id, cookies }) {
    const [quiz, setQuiz] = useState(null);
    const redirect = (page) => {
        window.location.href = page;
    };

    useEffect(() => {
        async function effect() {
            try {
                const data = await getQuiz(id, cookies);

                setQuiz(data);
            } catch (e) {
                redirect("/");
            }
        }
        effect();
    });

    return (
        <div className="mt-28 flex items-center justify-center flex-col">
            <div className="w-[800px] flex flex-row mb-6">
                {quiz && <h2 className="text-5xl w-1/2">{quiz.title}</h2>}
                <div className="text-[20px] flex justify-end w-full">
                    <button
                        className="flex flex-row justify-center items-center border-2 border-stone-200 py-2 px-4 rounded-3xl cursor-pointer hover:bg-stone-200 duration-500"
                        onClick={() => redirect(`/Author/Edit/${id}`)}
                    >
                        <FontAwesomeIcon
                            icon={faPencil}
                            className="text-[15px] mr-1"
                        ></FontAwesomeIcon>
                        <div className="">Edit</div>
                    </button>
                </div>
            </div>
            {quiz &&
                quiz.questions.map((question, index) => {
                    return <Game question={question} />;
                })}
        </div>
    );
}
