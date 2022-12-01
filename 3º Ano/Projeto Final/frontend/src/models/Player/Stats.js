import { useState, useEffect } from "react";
import { getQuiz } from "./Game/API_game";

export default function Stats({ results, cookies }) {
    const [quiz, setQuiz] = useState(null);
    const redirect = (page) => {
        window.location.href = page;
    };

    const percent = () => {
        const score = results[1];
        const total = results[2];
        const percentage = score / total;
        return percentage;
    };

    const evaluate = () => {
        const percentage = percent();

        if (0 <= percentage && percentage < 0.5)
            return "Better luck next time.";
        else if (0.5 <= percentage && percentage < 0.7) return "Keep working!";
        else if (0.7 <= percentage && percentage < 0.9) return "Nice work!";
        else if (0.9 <= percentage) return "Congratulations!";
    };

    useEffect(() => {
        async function effect() {
            try {
                const data = await getQuiz(results[0], cookies);

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
                {quiz && (
                    <h2 className="text-5xl w-full flex justify-center">
                        {quiz.title}
                    </h2>
                )}
            </div>
            <div className="w-[350px] lg:w-[800px] text-2xl flex justify-center">
                You scored {parseInt(percent() * 100)}/100!
            </div>
            <div className="text-xl mt-2">{evaluate()}</div>
            <button
                className="mt-3 border-2 px-4 rounded-3xl py-2 text-lg hover:bg-stone-200 duration-1000"
                onClick={(e) => redirect("/Player/Main")}
            >
                Play another quiz
            </button>
        </div>
    );
}
