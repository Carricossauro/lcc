import { useEffect, useState } from "react";
import Game from "./Game";
import { getQuiz, sendAnswer } from "./API_game";

export default function Quiz({ id, cookies }) {
    const [quiz, setQuiz] = useState(null);
    const [answers, setAnswers] = useState({});

    const redirect = (page) => {
        window.location.href = page;
    };

    const totalScore = () => {
        let total = 0;

        for (var questionIndex in quiz.questions)
            total += quiz.questions[questionIndex].score;

        return total;
    };

    async function submit(e) {
        try {
            let correct = 0;
            for (var questionIndex in quiz.questions) {
                if (answers[questionIndex]) {
                    const data = await sendAnswer(
                        answers[questionIndex],
                        quiz.questions[questionIndex].id,
                        cookies
                    );

                    if (data.correct)
                        correct += quiz.questions[questionIndex].score;
                }
            }

            redirect(`/Player/Game/Stats/${id}-${correct}-${totalScore()}`);
        } catch (e) {
            redirect("/");
        }
    }

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
        <div className="mt-28 flex items-center justify-center flex-col">
            <div className="w-[350px] lg:w-[800px] flex flex-row mb-6">
                {quiz && <h2 className="text-5xl w-2/3">{quiz.title}</h2>}
            </div>
            {quiz &&
                quiz.questions.map((question, index) => {
                    return (
                        <>
                            {" "}
                            <div className="w-[350px] lg:w-[800px] text-3xl mt-6">
                                Question {index + 1}
                            </div>
                            <hr className="h bg-gray-900 w-[350px] lg:w-[900px] mt-2 mb-5" />
                            <Game
                                question={question}
                                answers={answers}
                                setAnswers={setAnswers}
                                questionIndex={index}
                                key={`q${index}`}
                            />
                        </>
                    );
                })}
            <div className="w-[350px] lg:w-[800px] flex justify-end mt-6">
                <button
                    className="flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3"
                    onClick={submit}
                >
                    Submit
                </button>
            </div>
        </div>
    );
}
