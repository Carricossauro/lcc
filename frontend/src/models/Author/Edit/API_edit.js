export async function sendQuestion(question, cookies) {
    const token = cookies["access_token"];
    const username = cookies["username"];

    const requestOptions = {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
        },
        body: JSON.stringify({
            title: question.title,
            type: question.type,
            score: question.score,
            dificulty: question.difficulty[0],
            minage: question.minage,
            contents: question.contents,
            options: question.options,
        }),
    };

    const url = `${process.env.REACT_APP_API_URL}/api/questions/insert/`;

    console.log(requestOptions);

    const response = await fetch(url, requestOptions);

    return response.ok;
}

export async function getQuestion(id, cookies) {
    const token = cookies["access_token"];

    const requestOptions = {
        method: "GET",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
        },
    };

    const url = `${process.env.REACT_APP_API_URL}/api/questions/${id}`;

    const response = await fetch(url, requestOptions);

    if (!response.ok) throw new Error();

    const data = await response.json();

    return data;
}

export async function updateQuestion(question, cookies) {
    const token = cookies["access_token"];

    const requestOptions = {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
        },
        body: JSON.stringify({
            title: question.title,
            type: question.type,
            score: question.score,
            dificulty: question.difficulty[0],
            minage: question.minage,
            contents: question.content,
            options: question.options,
        }),
    };

    const url = `${process.env.REACT_APP_API_URL}/api/questions/update/`;

    const response = await fetch(url, requestOptions);

    return response.ok;
}
