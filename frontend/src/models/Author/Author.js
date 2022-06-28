import { React, useEffect, useState } from "react";
import { useParams } from "react-router-dom";
import Gamelist from "../Gamelist/Gamelist";
import Main from "./Main";
import Edit from "./Edit/Edit";
import { confirmType } from "../../API_index";
import Game from "./Game/Game";
import Quiz from "./Game/Quiz";

export default function Author({
    setShowNavBar,
    size,
    cookies,
    removeCookies,
    game,
    edit,
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

    if (edit) {
        return <Edit size={size} cookies={cookies} id={authorPath} />;
    } else if (game) {
        return <Quiz id={authorPath} cookies={cookies} />;
    } else
        switch (authorPath) {
            case "Explore":
                return (
                    <Gamelist
                        cookies={cookies}
                        removeCookies={removeCookies}
                        authorRedirect={true}
                    />
                );
            case "Mygames":
                return (
                    <Gamelist
                        author={username}
                        cookies={cookies}
                        removeCookies={removeCookies}
                        authorRedirect={true}
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
