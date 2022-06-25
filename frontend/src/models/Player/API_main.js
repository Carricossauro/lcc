export async function getQuestions() {
    const requestOptions = {
        method: "GET",
        headers: { "Content-Type": "application/json" },
    };

    const url = `${process.env.REACT_APP_API_URL}/api/questions/`;

    const response = await fetch(url, requestOptions);

    if (!response.ok) return null;
    const data = await response.json();
    return data;
}
