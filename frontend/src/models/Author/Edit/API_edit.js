export async function sendQuestion(question) {
    const requestOptions = {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            title: question.title,
            author: question.author,
            type: question.type,
            score: question.score,
            dificulty: question.difficulty[0],
            minage: question.minage,
            contents: question.content,
            options: question.options,
        }),
    };

    console.log(requestOptions.body);

    const url = `${process.env.REACT_APP_API_URL}/api/questions/`;

    const response = await fetch(url, requestOptions);

    return response.ok;
}
