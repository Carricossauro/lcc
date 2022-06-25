import React, { useEffect, useState } from "react";
import { getQuestions } from "./API_main";

export default function Main() {
    const [games, setGames] = useState([]);

    const redirect = (page) => {
        window.location.href = page;
    };

    useEffect(() => {
        async function effect() {
            const data = await getQuestions();

            setGames(data);
        }
        effect();
    }, []);

    return (
        <>
            <div className="w-4/5 m-auto mt-28 pt-3">
                <div className="relative z-20 flex flex-col justify-center h-full px-3 mx-auto flex-center">
                    <div className="relative items-center pl-1 flex w-full lg:max-w-68 sm:pr-2 sm:ml-0">
                        <div className="container relative left-0 z-50 flex w-3/4 h-auto h-full">
                            <div className="relative flex items-center w-full lg:w-64 h-full group">
                                <svg
                                    className="absolute left-0 z-20 hidden w-4 h-4 ml-4 text-gray-500 pointer-events-none fill-current group-hover:text-gray-400 sm:block"
                                    xmlns="http://www.w3.org/2000/svg"
                                    viewBox="0 0 20 20"
                                >
                                    <path d="M12.9 14.32a8 8 0 1 1 1.41-1.41l5.35 5.33-1.42 1.42-5.33-5.34zM8 14A6 6 0 1 0 8 2a6 6 0 0 0 0 12z"></path>
                                </svg>
                                <input
                                    type="text"
                                    className="block w-full py-1.5 pl-10 pr-4 leading-normal rounded-2xl focus:border-transparent focus:outline-none focus:ring-2 focus:ring-blue-500 ring-opacity-90 bg-gray-100  text-gray-400 aa-input"
                                    placeholder="Search"
                                />
                                <div className="absolute right-0 hidden h-auto px-2 py-1 mr-2 text-xs text-gray-400 border border-gray-300 rounded-2xl md:block">
                                    +
                                </div>
                            </div>
                        </div>
                        {/* <div className="relative p-1 flex items-center justify-end w-1/4 ml-5 mr-4 sm:mr-0 sm:right-auto">
                          <a href="#" className="block relative">
                            <img
                              alt="profil"
                              src="/images/person/1.jpg"
                              className="mx-auto object-cover rounded-full h-10 w-10 "
                            />
                          </a>
                        </div> */}
                    </div>
                </div>

                <div className="h-[640px] overflow-scroll rounded-lg shadow-xl mt-8">
                    <table className="w-full ">
                        <thead className="sticky top-0">
                            <tr className="">
                                <th className="px-4 py-4 text-left bg-blue-900 text-white text-sm font-medium w-1/3 text-center rounded-tl-lg">
                                    Title
                                </th>
                                <th className="px-4 py-4 text-left bg-blue-900 text-white text-sm font-medium w-1/3 text-center">
                                    Author
                                </th>
                                <th className="px-4 py-4 text-left bg-blue-900 text-white text-sm font-medium text-center">
                                    Difficulty
                                </th>
                                <th className="px-4 py-4 text-left bg-blue-900 text-white text-sm font-medium text-center">
                                    Minimum Age
                                </th>
                                <th className="px-4 py-4 text-left bg-blue-900 text-white text-sm font-medium text-center rounded-tr-lg">
                                    Type
                                </th>
                            </tr>
                        </thead>
                        <tbody>
                            {games.map((question, index) => {
                                return (
                                    <tr
                                        className={`border-gray-200 even:bg-gray-200 cursor-pointer`}
                                        id={index}
                                        key={index}
                                        onClick={() =>
                                            redirect(
                                                `/Player/Game/${question.id}`
                                            )
                                        }
                                    >
                                        <td className="px-4 py-8 border-t border-b border-gray-200 text-sm text-center">
                                            {question.title}
                                        </td>
                                        <td className="px-4 py-8 border-t border-b border-gray-200 text-sm text-center">
                                            {question.author}
                                        </td>
                                        <td className="px-4 py-8 border-t border-b border-gray-200 text-sm text-center">
                                            {question.dificulty}
                                        </td>
                                        <td className="px-4 py-8 border-t border-b border-gray-200 text-sm text-center">
                                            {question.minage}
                                        </td>
                                        <td className="px-4 py-8 border-t border-b border-gray-200 text-sm text-center">
                                            {question.type}
                                        </td>
                                    </tr>
                                );
                            })}
                        </tbody>
                    </table>
                </div>
            </div>
        </>
    );
}
