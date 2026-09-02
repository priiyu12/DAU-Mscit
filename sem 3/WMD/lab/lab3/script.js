// --- Product Data ---
const products = [
    { id: 1, name: "Chocolate Fudge Cake", price: 25.00, image: "https://images.unsplash.com/photo-1578985545062-69928b1d9587?w=300&h=200&fit=crop" },
    { id: 2, name: "Blueberry Muffins (6-pack)", price: 12.00, image: "https://images.unsplash.com/photo-1587668178277-295251f900ce?w=300&h=200&fit=crop" },
    { id: 3, name: "Assorted Cookie Tin", price: 18.50, image: "https://images.unsplash.com/photo-1499636136210-6f4ee915583e?w=300&h=200&fit=crop" },
    { id: 4, name: "Red Velvet Cupcakes", price: 15.00, image: "https://images.unsplash.com/photo-1614707267537-b85aaf00c4b7?w=300&h=200&fit=crop" },
    { id: 5, name: "Lemon Drizzle Cake", price: 22.00, image: "https://images.unsplash.com/photo-1519869325930-281384150729?w=300&h=200&fit=crop" },
    { id: 6, name: "Macaron Gift Box", price: 30.00, image: "https://images.unsplash.com/photo-1569864358642-9d1684040f43?w=300&h=200&fit=crop" }
];

// --- State ---
let cart = [];

// --- DOM Elements ---
const productContainer = document.getElementById('product-container');
const searchInput = document.getElementById('search-input');
const cartItemsContainer = document.getElementById('cart-items');
const cartTotalElement = document.getElementById('cart-total');
const cartCountElement = document.getElementById('cart-count');
const couponForm = document.getElementById('coupon-form');
const couponMessage = document.getElementById('coupon-message');

// --- 1. Render Products (DOM Manipulation) ---
function renderProducts(items) {
    productContainer.innerHTML = '';
    
    if (items.length === 0) {
        productContainer.innerHTML = '<p>No treats found matching your search.</p>';
        return;
    }

    items.forEach((product, index) => {
        const card = document.createElement('div');
        card.className = 'product-card scroll-animate';
        // Add a slight stagger delay to the animation
        card.style.transitionDelay = `${index * 0.05}s`;
        card.dataset.id = product.id; // Store ID for delegation
        
        card.innerHTML = `
            <div class="image-wrapper">
                <img src="${product.image}" alt="${product.name}" class="product-image">
            </div>
            <div class="product-info">
                <div class="product-name">${product.name}</div>
                <div class="product-price">$${product.price.toFixed(2)}</div>
            </div>
            <button class="add-to-cart-btn">
                <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="margin-right: 5px;">
                    <path d="M6 2L3 6v14a2 2 0 0 0 2 2h14a2 2 0 0 0 2-2V6l-3-4z"></path>
                    <line x1="3" y1="6" x2="21" y2="6"></line>
                    <path d="M16 10a4 4 0 0 1-8 0"></path>
                </svg>
                Add to Cart
            </button>
            <div class="quick-view-tooltip">Quick view: ${product.name}</div>
        `;
        
        // mouseover / mouseout for quick-view tooltip
        card.addEventListener('mouseover', (e) => {
            card.classList.add('hovered');
        });
        card.addEventListener('mouseout', (e) => {
            card.classList.remove('hovered');
        });

        productContainer.appendChild(card);
    });

    // Re-observe new cards for scroll animation
    const newCards = document.querySelectorAll('.scroll-animate');
    newCards.forEach(el => observer.observe(el));
}

// --- Scroll Animations (Intersection Observer) ---
const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.classList.add('visible');
        }
    });
}, { threshold: 0.1 });

// Initial render
renderProducts(products);


// --- 2. Event Delegation for Cart Actions ---
productContainer.addEventListener('click', function(event) {
    // Check if the clicked element has the class 'add-to-cart-btn'
    if (event.target.classList.contains('add-to-cart-btn')) {
        // Use closest() to find the parent product card and its ID
        const card = event.target.closest('.product-card');
        if (card) {
            const productId = parseInt(card.dataset.id);
            const product = products.find(p => p.id === productId);
            addToCart(product);
        }
    }
});


// --- 3. Cart Logic & Custom Event ---
function addToCart(product) {
    const existingItem = cart.find(item => item.id === product.id);
    
    if (existingItem) {
        existingItem.quantity += 1;
    } else {
        cart.push({ ...product, quantity: 1 });
    }

    // Console panel requirements
    console.group(`Added to cart: ${product.name}`);
    console.log("Cart updated. Current items:");
    console.table(cart);
    console.groupEnd();

    // Dispatch custom event
    dispatchCartUpdate();
}

function updateQuantity(id, change) {
    const item = cart.find(item => item.id === id);
    if (item) {
        item.quantity += change;
        if (item.quantity <= 0) {
            cart = cart.filter(i => i.id !== id);
        }
        dispatchCartUpdate();
    }
}

function removeItem(id) {
    cart = cart.filter(item => item.id !== id);
    dispatchCartUpdate();
}

// Dispatch a custom event instead of calling renderCart() directly
function dispatchCartUpdate() {
    const event = new CustomEvent('cart:updated', { 
        detail: { cartContents: cart }
    });
    document.dispatchEvent(event);
}

// Listen for the custom event to update the UI
document.addEventListener('cart:updated', (e) => {
    renderCart(e.detail.cartContents);
});

function renderCart(cartData) {
    if (cartData.length === 0) {
        cartItemsContainer.innerHTML = '<p class="empty-cart-msg">Your cart is empty.</p>';
        cartTotalElement.textContent = '0.00';
        return;
    }

    let html = '';
    let total = 0;
    let count = 0;

    cartData.forEach(item => {
        total += item.price * item.quantity;
        count += item.quantity;
        html += `
            <div class="cart-item">
                <div class="cart-item-details">
                    <div class="cart-item-title">${item.name}</div>
                    <div class="cart-item-price">$${item.price.toFixed(2)} x ${item.quantity}</div>
                </div>
                <div class="cart-item-controls">
                    <button onclick="updateQuantity(${item.id}, -1)">-</button>
                    <span>${item.quantity}</span>
                    <button onclick="updateQuantity(${item.id}, 1)">+</button>
                    <button class="btn-remove" onclick="removeItem(${item.id})">
                        <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                            <line x1="18" y1="6" x2="6" y2="18"></line>
                            <line x1="6" y1="6" x2="18" y2="18"></line>
                        </svg>
                    </button>
                </div>
            </div>
        `;
    });

    cartItemsContainer.innerHTML = html;
    cartTotalElement.textContent = total.toFixed(2);
    if(cartCountElement) cartCountElement.textContent = count;
}


// --- 4. Debounce Search Input (keydown/keyup) ---
// Debouncing prevents the filter function from running on every single keystroke.
// It waits until the user stops typing (e.g., for 300ms) before executing.
// This matters for performance, especially with large datasets or complex filtering/API calls,
// as it reduces main thread blocking and layout thrashing.
function debounce(func, delay) {
    let timeoutId;
    return function(...args) {
        clearTimeout(timeoutId);
        timeoutId = setTimeout(() => {
            func.apply(this, args);
        }, delay);
    };
}

const handleSearch = debounce((event) => {
    const query = event.target.value.toLowerCase();
    const filtered = products.filter(p => p.name.toLowerCase().includes(query));
    renderProducts(filtered);
    
    // Log key event object properties as required
    console.log("Search executed. Event details:", {
        type: event.type,
        target: event.target,
        currentTarget: event.currentTarget,
        timeStamp: event.timeStamp,
        key: event.key
    });
}, 300);

// We attach keyup so we capture the value after the key is released
searchInput.addEventListener('keyup', handleSearch);


// --- 5. Coupon Form (submit & preventDefault) ---
couponForm.addEventListener('submit', (e) => {
    // Prevent the page from refreshing
    e.preventDefault();
    
    const code = document.getElementById('coupon-code').value.trim().toUpperCase();
    
    if (code === 'SWEET10') {
        couponMessage.textContent = "10% Discount applied! (Visual only)";
        couponMessage.className = 'success';
    } else {
        couponMessage.textContent = "Invalid coupon code.";
        couponMessage.className = 'error';
    }
});


// --- 6. Advanced Event Handling: Bubbling vs Capturing ---
const parentBox = document.getElementById('parent-box');
const childBox = document.getElementById('child-box');

// Capturing phase (fires first, top-down)
parentBox.addEventListener('click', (e) => {
    console.log('1. Parent Box Clicked! (Capturing Phase)');
}, true); // true = useCapture

childBox.addEventListener('click', (e) => {
    console.log('2. Child Box Clicked! (Capturing Phase)');
}, true);

// Bubbling phase (fires second, bottom-up)
childBox.addEventListener('click', (e) => {
    console.log('3. Child Box Clicked! (Bubbling Phase)');
    // Uncomment the next line to demonstrate stopping propagation
    // e.stopPropagation(); 
}, false); // false is default

parentBox.addEventListener('click', (e) => {
    console.log('4. Parent Box Clicked! (Bubbling Phase)');
}, false);


// --- 7. Memory Profiling & Leak Detection Demo ---
const leakContainer = document.getElementById('leak-container');
let detachedNodes = []; // Holding a reference simulates a severe leak

function dummyHandler() {
    console.log("Leak item clicked");
}

document.getElementById('btn-leak').addEventListener('click', () => {
    for(let i=0; i<100; i++) {
        const div = document.createElement('div');
        div.className = 'leak-item';
        div.textContent = 'Leaked Node ' + i;
        div.addEventListener('click', dummyHandler);
        leakContainer.appendChild(div);
    }
    console.log("Added 100 items.");
});

document.getElementById('btn-clear').addEventListener('click', () => {
    // To GUARANTEE a leak in modern browsers, we save the nodes to a global array
    // before clearing them from the DOM.
    const nodes = Array.from(leakContainer.querySelectorAll('.leak-item'));
    detachedNodes = detachedNodes.concat(nodes);
    
    leakContainer.innerHTML = '';
    console.log("Cleared from DOM, but stored in global array (Memory Leak).");
});

document.getElementById('btn-fix').addEventListener('click', () => {
    // Fix: Properly remove listeners and clear from our global array
    const nodes = Array.from(leakContainer.querySelectorAll('.leak-item'));
    nodes.forEach(item => {
        item.removeEventListener('click', dummyHandler);
    });
    
    // Clear the array to allow Garbage Collection
    detachedNodes = []; 
    leakContainer.innerHTML = '';
    console.log("Cleared DOM and removed global references (Fixed).");
});
