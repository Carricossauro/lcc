export async function getGame(id, cookies) {
    const token = cookies["access_token"];

    const url = `${process.env.REACT_APP_API_URL}/api/questions/${id}`;

    const requestOptions = {
        method: "GET",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
        },
    };

    const response = await fetch(url, requestOptions);

    const data = await response.json();

    return { response, data };
}
