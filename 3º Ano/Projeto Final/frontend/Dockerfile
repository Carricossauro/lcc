# Stage 1: build
FROM node:14.18.1-alpine3.14 AS build

WORKDIR /app

# Install npm dependencies.
COPY package*.json ./
RUN npm ci --only prod --progress false --loglevel error --no-audit

ARG REACT_APP_API_URL
ENV REACT_APP_API_URL $REACT_APP_API_URL

# Build artificats.
COPY . .
RUN npm run build

# Stage 2: server
FROM nginx:stable-alpine
COPY --from=build /app/build /usr/share/nginx/html
COPY ./nginx.conf /etc/nginx/conf.d/default.conf
EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]
