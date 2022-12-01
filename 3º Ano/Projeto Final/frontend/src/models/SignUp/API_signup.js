const titleCase = (str) => {
    return str.charAt(0).toUpperCase() + str.substr(1).toLowerCase();
};

export async function sendUser(user, setErrorLocation) {
    const requestOptions = {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            username: user.username,
            name: user.name,
            password: user.password,
            email: user.email,
            birthday: user.birthday,
            type: user.type,
        }),
    };

    const url = `${process.env.REACT_APP_API_URL}/api/users/`;

    try {
        const response = await fetch(url, requestOptions);

        const data = await response.json();
        if (response.ok) return data;

        const checkList = ["username", "name", "email", "password", "birthday"];
        for (var check of checkList) {
            if (check in data) {
                if (data[check][0] === "This field may not be blank.") {
                    setErrorLocation(check);
                    throw `${titleCase(check)} may not be blank.`;
                }
                if (
                    data[check][0] ===
                    "Date has wrong format. Use one of these formats instead: YYYY-MM-DD."
                ) {
                    setErrorLocation("birthday");
                    throw "Date is incorrect.";
                }
                setErrorLocation(check);
                throw data[check];
            }
        }
        throw "Unable to create account. Try again later.";
    } catch (e) {
        throw "Unable to create account. Try again later.";
    }
}
