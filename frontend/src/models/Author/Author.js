import { React, useEffect, useState } from "react";
import { useParams } from "react-router-dom";
import Gamelist from "../Gamelist/Gamelist";
import Main from "./Main";
import Edit from "./Edit/Edit";
import { confirmType } from "../../API_index";

export default function Author({
    setShowNavBar,
    size,
    cookies,
    removeCookies,
}) {
    const redirect = (page) => {
        window.location.href = page;
    };
    const { authorPath } = useParams();
    const [username, setUsername] = useState("");

    useEffect(() => {
        async function effect() {
            try {
                const token = cookies["access_token"];
                const c_username = cookies["username"];

                if (!token || !c_username) throw new Error();

                const correctUser = await confirmType(c_username, token, true);

                if (!correctUser) throw new Error();

                setUsername(c_username);
            } catch (e) {
                redirect("/");
            }
        }
        effect();
    }, []);

    switch (authorPath) {
        case "Explore":
            return <Gamelist />;
        case "Mygames":
            return (
                <Gamelist
                    author={username}
                    cookies={cookies}
                    removeCookies={removeCookies}
                />
            );
        case "Create":
            return <Edit size={size} cookies={cookies} />;
        case "Main":
            return <Main size={size} />;
        default:
            redirect("/Author/Main");
            break;
    }
}
