export async function getQuizzes(cookies) {
    const token = cookies["access_token"];

    const requestOptions = {
        method: "GET",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
        },
    };

    const url = `${process.env.REACT_APP_API_URL}/api/quizzes/`;

    const response = await fetch(url, requestOptions);

    if (!response.ok) return null;
    const data = await response.json();
    return data;
}
