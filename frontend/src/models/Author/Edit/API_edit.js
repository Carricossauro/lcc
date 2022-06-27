export async function sendQuestion(question, cookies, newQuestion) {
    const token = cookies["access_token"];
    const username = cookies["username"];

    for (var i in question.contents) {
        delete question.contents[i].question;
        if (!question.contents[i].media) delete question.contents[i].media;
    }

    for (var i in question.options) {
        delete question.options[i].question;
    }

    let body = {
        title: question.title,
        type: question.type,
        score: question.score,
        dificulty: question.dificulty[0],
        minage: question.minage,
        contents: question.contents,
        options: question.options,
    };

    const requestOptions = {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
        },
        body: JSON.stringify(body),
    };

    let url = "";

    if (newQuestion) {
        url = `${process.env.REACT_APP_API_URL}/api/questions/update/${newQuestion}`;
    } else url = `${process.env.REACT_APP_API_URL}/api/questions/insert/`;

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
