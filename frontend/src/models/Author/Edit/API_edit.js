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
            author: username,
            type: question.type,
            score: question.score,
            dificulty: question.difficulty[0],
            minage: question.minage,
            contents: question.content,
            options: question.options,
        }),
    };

    console.log(requestOptions.body);

    const url = `${process.env.REACT_APP_API_URL}/api/questions/insert/`;

    const response = await fetch(url, requestOptions);

    return response.ok;
}
