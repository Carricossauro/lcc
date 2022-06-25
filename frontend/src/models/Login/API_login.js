export async function login(username, password, isAuthor) {
    const requestOptions = {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            username: username,
            password: password,
            type: isAuthor ? "A" : "P",
        }),
    };

    const url = `${process.env.REACT_APP_API_URL}/api/login/`;

    const response = await fetch(url, requestOptions);

    const data = await response.json();

    if (!response.ok) throw new Error();

    return data;
}
