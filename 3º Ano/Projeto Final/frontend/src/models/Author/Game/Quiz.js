import { useEffect, useState } from "react";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faPencil } from "@fortawesome/free-solid-svg-icons";
import Game from "./Game";
import { getQuiz } from "./API_game";

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
    }, []);

    return (
        <div className="mt-28 flex items-center justify-center flex-col mb-10">
            <div className="w-[350px] lg:w-[800px] flex flex-row mb-6">
                {quiz && <h2 className="text-5xl w-2/3">{quiz.title}</h2>}
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
                    return (
                        <>
                            <div className="w-[350px] lg:w-[800px] text-3xl mt-6">
                                Question {index + 1}
                            </div>
                            <hr className="h bg-gray-900 w-[350px] lg:w-[900px] mt-2 mb-5" />
                            <Game question={question} />
                        </>
                    );
                })}
        </div>
    );
}
