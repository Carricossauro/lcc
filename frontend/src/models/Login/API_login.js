import { confirmType } from "../../API_index";

export async function login(username, password, isAuthor) {
    const requestOptions = {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            username: username,
            password: password,
        }),
    };

    const url = `${process.env.REACT_APP_API_URL}/api/login/`;

    try {
        const response = await fetch(url, requestOptions);

        const data = await response.json();

        if (!response.ok) throw "wrong";

        const correctType = await confirmType(username, data.access, isAuthor);

        if (!correctType) throw "type";

        return data;
    } catch (e) {
        throw e;
    }
}
