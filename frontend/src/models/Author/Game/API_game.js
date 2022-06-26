export async function getGame(id) {
    const url = `${process.env.REACT_APP_API_URL}/api/questions/${id}`;

    const requestOptions = {
        method: "GET",
        headers: { "Content-Type": "application/json" },
    };

    const response = await fetch(url, requestOptions);

    const data = await response.json();

    return { response, data };
}
