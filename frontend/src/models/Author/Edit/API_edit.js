export async function sendQuestion(question) {
    const requestOptions = {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            title: question.title,
            author: question.author,
            type: question.type,
            score: question.score,
            dificulty: question.difficulty,
            minage: question.minage,
        }),
    };

    const url = `${process.env.REACT_APP_API_URL}/api/questions/`;

    const response = await fetch(url, requestOptions);

    if (!response.ok) return null;
    const data = await response.json();
    return data.id;
}

export async function sendOption(option, id) {
    const requestOptions = {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            question: id,
            answer: option.answer,
            correct: option.correct,
        }),
    };

    const url = `${process.env.REACT_APP_API_URL}/api/option/`;

    const response = await fetch(url, requestOptions);

    if (!response.ok) return null;
    return await response.json();
}

export async function sendContentText(content, id, index) {
    const requestOptions = {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            question: id,
            order: index,
            type: content.type,
            text: content.media,
        }),
    };

    const url = `${process.env.REACT_APP_API_URL}/api/content/`;

    const response = await fetch(url, requestOptions);

    if (!response.ok) return null;
    return await response.json();
}
