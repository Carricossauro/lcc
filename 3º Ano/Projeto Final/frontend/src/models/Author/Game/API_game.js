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
