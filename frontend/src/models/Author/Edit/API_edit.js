export async function sendQuiz(questions, cookies, newQuestion, title) {
    const token = cookies["access_token"];

    for (var questionIndex in questions) {
        let question = questions[questionIndex];
        delete question.id;
        delete question.author;
        delete question.quiz;

        for (var i in question.contents) {
            delete question.contents[i].question;
            delete question.contents[i].id;
            if (!question.contents[i].media) delete question.contents[i].media;
        }

        for (var i in question.options) {
            delete question.options[i].question;
            delete question.options[i].id;
        }
    }

    const requestOptions = {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
        },
        body: JSON.stringify({ questions: questions, title: title }),
    };

    let url = "";

    console.log(requestOptions.body);

    if (newQuestion) {
        url = `${process.env.REACT_APP_API_URL}/api/quizzes/update/${newQuestion}`;
    } else url = `${process.env.REACT_APP_API_URL}/api/quizzes/insert/`;

    const response = await fetch(url, requestOptions);

    return response.ok;
}

export async function getQuiz(id, cookies) {
    const token = cookies["access_token"];

    const requestOptions = {
        method: "GET",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
        },
    };

    const url = `${process.env.REACT_APP_API_URL}/api/quizzes/${id}`;

    const response = await fetch(url, requestOptions);

    if (!response.ok) throw new Error();

    const data = await response.json();

    return data;
}
