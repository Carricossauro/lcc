export async function getGame(id) {
    const url = `${process.env.REACT_APP_API_URL}/api/questions/${id}`;

    const requestOptions = {
        method: "GET",
        headers: { "Content-Type": "application/json" },
    };

    const response = await fetch(url, requestOptions);

    const data = await response.json();

    return { response, data };
}

export async function sendAnswer(answer, question) {
    const url = `${process.env.REACT_APP_API_URL}/api/history/`;

    const requestOptions = {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            answer: answer,
            player: "sauro",
            question: question,
        }),
    };

    const response = await fetch(url, requestOptions);

    const data = await response.json();

    if (response.ok) return data;
    else throw new Error();
}
