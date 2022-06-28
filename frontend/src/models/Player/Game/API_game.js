export async function getQuiz(id, cookies) {
    const token = cookies["access_token"];

    const url = `${process.env.REACT_APP_API_URL}/api/quizzes/${id}`;

    const requestOptions = {
        method: "GET",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
        },
    };

    const response = await fetch(url, requestOptions);

    if (!response.ok) throw new Error();
    const data = await response.json();

    return data;
}

export async function sendAnswer(answer, question, cookies) {
    const token = cookies["access_token"];

    const url = `${process.env.REACT_APP_API_URL}/api/history/`;

    const requestOptions = {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
        },
        body: JSON.stringify({
            answer: answer,
            question: question,
        }),
    };

    console.log(requestOptions.body);

    const response = await fetch(url, requestOptions);

    const data = await response.json();

    if (response.ok) return data;
    else throw new Error();
}
