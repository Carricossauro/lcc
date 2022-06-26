import { useEffect, useState } from "react";

import GameTF from "./GameTF";
import GameMC from "./GameMC";
import GameSA from "./GameSA";

import { getGame, sendAnswer } from "./API_game";

export default function Game({ id, cookies }) {
    const [question, setQuestion] = useState({
        id: -1,
        title: "Title",
        author: "Author",
        type: "TF",
        score: "0",
        difficulty: "Easy",
        minage: 5,
        maxage: 10,
        options: [
            { answer: "True", correct: 1 },
            { answer: "False", correct: 0 },
        ],
        contents: [
            {
                media: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam egestas mauris mi, quis sollicitudin dui vestibulum at. Cras tortor est, imperdiet vitae nisl in, luctus tincidunt arcu. Aenean vehicula pellentesque laoreet. Pellentesque ornare consequat fermentum. Nulla finibus quam at risus placerat, feugiat sagittis mauris blandit. Phasellus facilisis orci dui, at congue felis viverra iaculis. Nunc a pulvinar risus. Nullam massa purus, tristique at sapien rhoncus, imperdiet tincidunt mauris. Vivamus fringilla accumsan interdum. In ante nisl, tristique ultricies justo sit amet, suscipit ornare ex. Nullam fermentum vel diam ut pulvinar. Aenean id augue id lacus posuere pulvinar malesuada eget velit. Curabitur luctus, magna eu placerat posuere, magna orci tempor justo, a scelerisque elit ex eu odio. Maecenas quam elit, fermentum quis mattis eu, placerat et lacus. Phasellus non lacinia sem, id condimentum leo. Pellentesque ullamcorper, mauris nec bibendum tristique, dui libero suscipit eros, ac convallis ipsum leo vel dolor. Sed ullamcorper vel nunc sed pellentesque. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Integer libero odio, accumsan nec metus non, bibendum scelerisque ex. Curabitur egestas hendrerit tristique. Aliquam lobortis venenatis ante sit amet finibus. In vel augue in tellus molestie bibendum. Curabitur mollis semper magna, non consequat massa consequat vitae. Maecenas sed purus augue. Vivamus luctus neque id elit commodo fermentum. Nullam pellentesque eleifend purus in fermentum. Nunc rhoncus augue augue, eu faucibus lectus egestas vel.",
                type: "T",
            },
            {
                media: "Aenean id augue id lacus posuere pulvinar malesuada eget velit. Curabitur luctus, magna eu placerat posuere, magna orci tempor justo, a scelerisque elit ex eu odio. Maecenas quam elit, fermentum quis mattis eu, placerat et lacus. Phasellus non lacinia sem, id condimentum leo. Pellentesque ullamcorper, mauris nec bibendum tristique, dui libero suscipit eros, ac convallis ipsum leo vel dolor. Sed ullamcorper vel nunc sed pellentesque. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Integer libero odio, accumsan nec metus non, bibendum scelerisque ex. Curabitur egestas hendrerit tristique. Aliquam lobortis venenatis ante sit amet finibus. In vel augue in tellus molestie bibendum. Curabitur mollis semper magna, non consequat massa consequat vitae. Maecenas sed purus augue. Vivamus luctus neque id elit commodo fermentum. Nullam pellentesque eleifend purus in fermentum. Nunc rhoncus augue augue, eu faucibus lectus egestas vel.",
                type: "T",
            },
        ],
    });
    const [answer, setAnswer] = useState();
    const redirect = (page) => {
        window.location.href = page;
    };

    async function submitAnswer() {
        const response = await sendAnswer(answer, question.id, cookies);

        if (response.correct) redirect("/Player/Correct");
        else redirect("/Player/Incorrect");
    }

    useEffect(() => {
        async function effect() {
            const { response, data } = await getGame(id);

            if (response.ok) setQuestion(data);
            else redirect("/Player/Main/");
        }
        effect();
    }, []);

    return (
        <>
            <div className="mt-28 flex items-center justify-center flex-col mb-16">
                <div className="flex items-center justify-center px-3 h-12 w-[800px] mb-3 text-5xl">
                    {question.title}
                </div>
                {question.contents.map((media, index) => {
                    switch (media["type"]) {
                        case "T":
                            return (
                                <div
                                    className="flex items-center px-3 w-[800px] min-h-[48px] text-justify rounded-3xl mb-3"
                                    key={index}
                                >
                                    {question.contents[index]["text"]}
                                </div>
                            );
                    }
                })}
                {question.type === "MC" && (
                    <GameMC
                        question={question}
                        answer={answer}
                        setAnswer={setAnswer}
                    />
                )}
                {question.type === "SA" && (
                    <GameSA answer={answer} setAnswer={setAnswer} />
                )}
                {question.type === "TF" && (
                    <GameTF
                        question={question}
                        answer={answer}
                        setAnswer={setAnswer}
                    />
                )}
                <div className="w-[800px] flex justify-end mt-6">
                    <button
                        className="flex items-center justify-center px-3 h-12 w-1/4 border-2 border-stone-200 rounded-3xl mb-3"
                        onClick={submitAnswer}
                    >
                        Submit
                    </button>
                </div>
            </div>
        </>
    );
}
