import React, { useState, useEffect } from "react";

import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import {
    faUser,
    faLock,
    faAddressCard,
    faEnvelope,
    faCalendar,
} from "@fortawesome/free-solid-svg-icons";

import image from "../../assets/imagem_conhecimento.jpg";
import { sendUser } from "./API_signup";
// import bcrypt from "bcryptjs";

export default function PlayerLogin({
    size,
    setShowNavBar,
    setIsAuthor,
    isAuthor,
    setCookie,
    cookies,
}) {
    const [username, setUsername] = useState("");
    const [name, setName] = useState("");
    const [password, setPassword] = useState("");
    const [confirmPassword, setConfirmPassword] = useState("");
    const [birthday, setBirthday] = useState("");
    const [email, setEmail] = useState("");
    const [error, setError] = useState("");
    const [errorLocation, setErrorLocation] = useState(null);

    const redirect = (page) => {
        window.location.href = page;
    };

    const validEmail = new RegExp(
        "^[a-zA-Z0-9._:$!%-]+@[a-zA-Z0-9.-]+.[a-zA-Z]$"
    );

    async function submitForm(e) {
        e.preventDefault();

        if (password != confirmPassword) {
            setErrorLocation("password");
            setError("Passwords do not match.");
        } else if (!validEmail.test(email)) {
            setErrorLocation("email");
            setError("Invalid email address :(");
        } else if (password === "") {
            setErrorLocation("password");
            setError("Password  may not be blank.");
        } else {
            const user = {
                username: username,
                name: name,
                password: password,
                email: email,
                birthday: birthday,
                type: isAuthor ? "A" : "P",
            };
            setError("");
            setErrorLocation(null);

            try {
                const response = await sendUser(user, setErrorLocation);

                // TODO - deal with authentication

                redirect(`/${isAuthor ? "Author" : "Player"}/Login`);
            } catch (e) {
                setError(e);
            }
        }
    }

    console.log(errorLocation);

    useEffect(() => {
        setShowNavBar(false);
    }, []);

    return (
        <div className="h-screen w-screen flex justify-center items-center bg-gradient-to-t from-white to-color2">
            <div className="bg-white min-h-[450px] h-[90%] w-[90%] lg:h-[700px] lg:w-[1200px] rounded-lg drop-shadow-xl flex flex-col">
                <div className="w-full h-[40px] bg-split-color2-white flex flex-row ">
                    <div
                        className={`w-1/2 flex justify-center items-center text-xl ${
                            !isAuthor
                                ? "bg-white rounded-tr-2xl "
                                : "bg-color2 rounded-br-2xl cursor-pointer text-slate-500 hover:text-slate-900 duration-200 "
                        }`}
                        onClick={() => {
                            setError("");
                            setIsAuthor(false);
                        }}
                    >
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
                            {isAuthor ? "Author" : "Player"} Sign Up
                        </div>
                        <div
                            className={`flex items-center px-3 h-12 w-96 bg-stone-200 border rounded-3xl mb-3 ${
                                errorLocation === "username"
                                    ? "border-red-800"
                                    : ""
                            }`}
                        >
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
                            className={`flex items-center px-3 h-12 w-96 bg-stone-200 border rounded-3xl mb-3 ${
                                errorLocation === "name" ? "border-red-800" : ""
                            }`}
                        >
                            <FontAwesomeIcon
                                icon={faAddressCard}
                                className="text-2xl  text-neutral-500 ml-2.5"
                            />
                            <input
                                className="outline-0 ml-3 bg-inherit w-full"
                                type="name"
                                id="name"
                                name="name"
                                value={name}
                                placeholder="name"
                                onChange={(e) => setName(e.target.value)}
                            ></input>
                        </div>
                        <div
                            className={`flex items-center px-3 h-12 w-96 bg-stone-200 border rounded-3xl mb-3 ${
                                errorLocation === "email"
                                    ? "border-red-800"
                                    : ""
                            }`}
                        >
                            <FontAwesomeIcon
                                icon={faEnvelope}
                                className="text-2xl  text-neutral-500 ml-2.5"
                            />
                            <input
                                className="outline-0 ml-3 bg-inherit w-full"
                                type="email"
                                id="email"
                                name="email"
                                value={email}
                                placeholder="email"
                                onChange={(e) => setEmail(e.target.value)}
                            ></input>
                        </div>
                        <div
                            className={`flex items-center px-3 h-12 w-96 bg-stone-200 border rounded-3xl mb-3 ${
                                errorLocation === "password"
                                    ? "border-red-800"
                                    : ""
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
                        <div
                            className={`flex items-center px-3 h-12 w-96 bg-stone-200 border rounded-3xl ${
                                !isAuthor
                                    ? "mb-3"
                                    : error == ""
                                    ? "mb-5"
                                    : "mb-1"
                            } ${
                                errorLocation === "password"
                                    ? "border-red-800"
                                    : ""
                            }`}
                        >
                            <FontAwesomeIcon
                                icon={faLock}
                                className="text-2xl  text-neutral-500 ml-2.5"
                            />
                            <input
                                className="outline-0 ml-3 bg-inherit w-full"
                                type="password"
                                id="confirmPassword"
                                name="confirmPassword"
                                value={confirmPassword}
                                placeholder="confirm password"
                                onChange={(e) =>
                                    setConfirmPassword(e.target.value)
                                }
                            ></input>
                        </div>
                        {!isAuthor && (
                            <div
                                className={`flex items-center px-3 h-12 w-96 bg-stone-200 border rounded-3xl ${
                                    error == "" ? "mb-5" : "mb-1"
                                } ${
                                    errorLocation === "birthday"
                                        ? "border-red-800"
                                        : ""
                                } text-neutral-500`}
                            >
                                <FontAwesomeIcon
                                    icon={faCalendar}
                                    className="text-2xl  text-neutral-500 ml-2.5"
                                />
                                <label className="ml-3 w-11/12">
                                    Enter your birthday
                                </label>
                                <input
                                    className="bg-transparent h-full w-full flex justify-end mr-2"
                                    type="date"
                                    id="birthday"
                                    name="birthday"
                                    value={birthday}
                                    onChange={(e) =>
                                        setBirthday(e.target.value)
                                    }
                                ></input>
                            </div>
                        )}
                        {error != "" && (
                            <div className="text-red-500 italic">{error}</div>
                        )}
                        <button
                            className="flex items-center justify-center h-12 w-96 rounded-3xl cursor-pointer bg-color1 text-lg hover:text-white duration-500"
                            onClick={(e) => submitForm(e)}
                        >
                            SIGN UP
                        </button>
                    </form>
                </div>
            </div>
        </div>
    );
}
