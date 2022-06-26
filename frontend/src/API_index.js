const redirect = (page) => {
    window.location.href = page;
};

export async function verify_login(cookies, removeCookie, setLoggedIn) {
    const token = cookies["access_token"];
    const username = cookies["username"];

    if (token && username) {
        const url = `${process.env.REACT_APP_API_URL}/api/login/verify/`;

        const requestOptions = {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ token: token }),
        };

        try {
            const response = await fetch(url, requestOptions);
            if (!response.ok) throw "token";

            const user_url = `${process.env.REACT_APP_API_URL}/api/users/${username}`;

            const user_requestOptions = {
                method: "GET",
                headers: {
                    "Content-Type": "application/json",
                    Authorization: `Bearer ${token}`,
                },
            };

            const user_response = await fetch(user_url, user_requestOptions);
            if (!user_response) throw "user";

            const data = await user_response.json();

            setLoggedIn(true);
            return [true, data];
        } catch (e) {
            console.log(e);
            cleanup(removeCookie, setLoggedIn);
            redirect("/");
        }
    }
    cleanup(removeCookie, setLoggedIn);
    return [false];
}

export function cleanup(removeCookie, setLoggedIn) {
    setLoggedIn(false);
    removeCookie("access_token");
    removeCookie("refresh_token");
    removeCookie("username");
}

export async function confirmType(username, token, isAuthor) {
    try {
        const url = `${process.env.REACT_APP_API_URL}/api/users/${username}`;

        const requestOptions = {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
                Authorization: `Bearer ${token}`,
            },
        };

        const response = await fetch(url, requestOptions);

        if (!response.ok) return false;

        const data = await response.json();

        const type = isAuthor ? "A" : "P";
        return data.type === type;
    } catch (e) {
        return false;
    }
}
