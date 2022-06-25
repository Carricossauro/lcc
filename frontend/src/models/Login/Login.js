import React, { useState, useEffect } from "react";

import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faUser, faLock } from "@fortawesome/free-solid-svg-icons";

// import bcrypt from "bcryptjs";

import image from "../../assets/imagem_conhecimento.jpg";
import { login } from "./API_login";

export default function PlayerLogin({
    size,
    setShowNavBar,
    setIsAuthor,
    isAuthor,
    setCookie,
    cookies,
}) {
    const [username, setUsername] = useState("");
    const [password, setPassword] = useState("");
    const [error, setError] = useState("");

    const [response, setResponse] = useState(undefined);

    useEffect(() => {
        setShowNavBar(false);
    }, []);

    const redirect = (page) => {
        window.location.href = page;
    };

    async function verifyLogin(e) {
        e.preventDefault();
        const url = `${process.env.REACT_APP_API_URL}/api/users/`;
        setError("");

        try {
            const response = await login(username, password, isAuthor);

            // TODO - deal with authentication

            redirect(`/${isAuthor ? "Author" : "Player"}/Main`);
        } catch (e) {
            setError("Invalid username or password.");
        }
    }

    return (
        <div className="h-screen w-screen flex justify-center items-center bg-gradient-to-t from-white to-color2">
            <div className="bg-white min-h-[450px] h-[90%] w-[90%] lg:h-[700px] lg:w-[1200px] rounded-lg drop-shadow-xl flex flex-col">
                <div className="w-full h-[40px] bg-split-color2-white flex flex-row ">
                    <div
                        className={`w-1/2 flex justify-center items-center text-xl ${
                            !isAuthor
                                ? "bg-white rounded-tr-2xl"
                                : "bg-color2 rounded-br-2xl cursor-pointer text-slate-500 hover:text-slate-900 duration-200"
                        }`}
                        onClick={() => {
                            setError("");
                            setIsAuthor(false);
                        }}
                    >
                        {" "}
                        Player
                    </div>
                    <div
                        className={`w-1/2 flex justify-center items-center text-xl ${
                            !isAuthor
                                ? "bg-color2 rounded-bl-2xl cursor-pointer text-slate-500 hover:text-slate-900 duration-200"
                                : "bg-white rounded-tl-2xl"
                        }`}
                        onClick={() => {
                            setError("");
                            setIsAuthor(true);
                        }}
                    >
                        {" "}
                        Author
                    </div>
                </div>
                <div className="w-full flex flex-row h-full">
                    {size >= 1024 && (
                        <div className="w-1/2 h-full flex items-center justify-center">
                            <img
                                src={image}
                                alt="image"
                                className="aspect-auto w-[500px] ml-10"
                            />
                        </div>
                    )}
                    <form className="w-full lg:w-1/2 flex justify-center flex-col items-center">
                        <div className="mb-8 text-3xl">
                            {isAuthor ? "Author" : "Player"} Login
                        </div>
                        <div className="flex items-center px-3 h-12 w-96 bg-stone-200  rounded-3xl mb-3">
                            <FontAwesomeIcon
                                icon={faUser}
                                className="text-2xl  text-neutral-500 ml-2.5"
                            />
                            <input
                                className="outline-0 ml-3 bg-inherit w-full"
                                type="text"
                                id="username"
                                name="username"
                                value={username}
                                placeholder="username"
                                onChange={(e) => setUsername(e.target.value)}
                            ></input>
                        </div>
                        <div
                            className={`flex items-center px-3 h-12 w-96 bg-stone-200  rounded-3xl ${
                                error != "" ? "mb-1" : "mb-5"
                            }`}
                        >
                            <FontAwesomeIcon
                                icon={faLock}
                                className="text-2xl  text-neutral-500 ml-2.5"
                            />
                            <input
                                className="outline-0 ml-3 bg-inherit w-full"
                                type="password"
                                id="password"
                                name="password"
                                value={password}
                                placeholder="password"
                                onChange={(e) => setPassword(e.target.value)}
                            ></input>
                        </div>
                        {error != "" && (
                            <div className="text-red-500 italic">{error}</div>
                        )}
                        <button
                            className="flex items-center justify-center h-12 w-96 rounded-3xl cursor-pointer bg-color1 text-lg"
                            onClick={(e) => verifyLogin(e)}
                        >
                            LOGIN
                        </button>
                        <div className="w-full text-center my-5">
                            ______________________
                        </div>
                        <div className="w-full text-center">
                            Don't have an account?
                        </div>
                        <div
                            className="w-full text-center mt-5 cursor-pointer hover:text-color1 hover:underline duration-100 font-bold"
                            onClick={() => redirect("/SignUp")}
                        >
                            Create an account now!
                        </div>
                    </form>
                </div>
            </div>
        </div>
    );
}
