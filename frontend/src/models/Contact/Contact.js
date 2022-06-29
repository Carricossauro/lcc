import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import {
    faAt,
    faLocationDot,
    faAddressCard,
    faEnvelope,
    faCalendar,
} from "@fortawesome/free-solid-svg-icons";
import { useState } from "react";

export default function Contact() {
    const [data, setData] = useState({
        first: "",
        last: "",
        email: "",
        message: "",
    });
    const [errorLocation, setErrorLocation] = useState(null);

    const validEmail = new RegExp(
        "^[a-zA-Z0-9._:$!%-]+@[a-zA-Z0-9.-]+.[a-zA-Z]$"
    );

    const submit = (e) => {
        if (!data.first) {
            setErrorLocation("first");
        } else if (!data.last) {
            setErrorLocation("last");
        } else if (!validEmail.test(data.email)) {
            setErrorLocation("email");
        } else if (!data.message) {
            setErrorLocation("message");
        } else setErrorLocation(null);
    };

    const change = (e) => {
        let newData = { ...data };
        newData[e.target.id] = e.target.value;

        setData(newData);
    };

    return (
        <div className="mt-32 flex items-center y-full px-8 sm:flex-row flex-col">
            <div className="flex flex-col lg:ml-20 mb-10 sm:items-start pr-0 sm:pr-4 w-full">
                <h1 className="text-5xl text-center sm:text-left font-bold tracking-wide text-color5 mb-8">
                    Contact Us
                </h1>
                <span className="text-base sm:text-xl flex items-center mb-4 text-gray-700">
                    <FontAwesomeIcon
                        icon={faAt}
                        className="text-lg sm:text-2xl w-8"
                    />
                    <p class="ml-2">computationalmind@di.uminho.pt</p>
                </span>
                <span className="text-base sm:text-xl flex text-gray-700">
                    <FontAwesomeIcon
                        icon={faLocationDot}
                        className="text-lg sm:text-2xl w-8 "
                    />
                    <div className="flex flex-col">
                        <p class="ml-2">
                            Departamento de Informática - Universidade do Minho
                        </p>
                        <p class="ml-3">4710-057, Braga</p>
                    </div>
                </span>
            </div>
            <form class="w-full sm:w-1/2 max-w-lg">
                <div class="flex flex-wrap -mx-3 mb-6">
                    <div class="w-full md:w-1/2 px-3 mb-6 md:mb-0">
                        <label
                            class="block uppercase tracking-wide text-gray-700 text-xs font-bold mb-2"
                            for="grid-first-name"
                        >
                            First Name
                        </label>
                        <input
                            class={`appearance-none block w-full bg-gray-200 text-gray-700 border ${
                                errorLocation === "first"
                                    ? "border-red-500"
                                    : "border-gray-200"
                            } rounded py-3 px-4 leading-tight focus:outline-none focus:bg-white`}
                            id="first"
                            type="text"
                            value={data.first}
                            placeholder="Jane"
                            onChange={change}
                        />
                        {errorLocation === "first" && (
                            <p class="text-red-500 text-xs italic mt-3">
                                Please fill out this field.
                            </p>
                        )}
                    </div>
                    <div class="w-full md:w-1/2 px-3">
                        <label
                            class="block uppercase tracking-wide text-gray-700 text-xs font-bold mb-2"
                            for="grid-last-name"
                        >
                            Last Name
                        </label>
                        <input
                            class={`appearance-none block w-full bg-gray-200 text-gray-700 border ${
                                errorLocation === "last"
                                    ? "border-red-500"
                                    : "border-gray-200"
                            } rounded py-3 px-4 leading-tight focus:outline-none focus:bg-white`}
                            id="last"
                            type="text"
                            value={data.last}
                            placeholder="Doe"
                            onChange={change}
                        />
                        {errorLocation === "last" && (
                            <p class="text-red-500 text-xs italic mt-3">
                                Please fill out this field.
                            </p>
                        )}
                    </div>
                </div>
                <div class="flex flex-wrap -mx-3 mb-6">
                    <div class="w-full px-3">
                        <label
                            class="block uppercase tracking-wide text-gray-700 text-xs font-bold mb-2"
                            for="grid-password"
                        >
                            E-mail
                        </label>
                        <input
                            class={`"appearance-none block w-full bg-gray-200 text-gray-700 border ${
                                errorLocation === "email"
                                    ? "border-red-500"
                                    : "border-gray-200"
                            } rounded py-3 px-4 mb-3 leading-tight focus:outline-none focus:bg-white`}
                            id="email"
                            value={data.email}
                            type="email"
                            onChange={change}
                        />
                        {errorLocation === "email" && (
                            <p class="text-red-500 text-xs italic">
                                Invalid email address.
                            </p>
                        )}
                    </div>
                </div>
                <div class="flex flex-wrap -mx-3 mb-6">
                    <div class="w-full px-3">
                        <label
                            class="block uppercase tracking-wide text-gray-700 text-xs font-bold mb-2"
                            for="grid-password"
                        >
                            Message
                        </label>
                        <textarea
                            class={`no-resize appearance-none block w-full bg-gray-200 text-gray-700 border ${
                                errorLocation === "message"
                                    ? "border-red-500"
                                    : "border-gray-200"
                            } rounded py-3 px-4 mb-3 leading-tight focus:outline-none focus:bg-white h-48 resize-none`}
                            id="message"
                            value={data.message}
                            onChange={change}
                        ></textarea>
                        {errorLocation === "message" && (
                            <p class="text-red-500 text-xs italic">
                                Please fill out this field.
                            </p>
                        )}
                    </div>
                </div>
                <div class="md:flex md:items-center mb-10">
                    <div class="md:w-1/3">
                        <button
                            class="shadow bg-color1 hover:bg-teal-400 focus:shadow-outline focus:outline-none text-white font-bold py-2 px-4 rounded"
                            type="button"
                            onClick={submit}
                        >
                            Send
                        </button>
                    </div>
                </div>
            </form>
        </div>
    );
}
